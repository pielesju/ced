/* editor.c
 * CED - Code EDitor
 * Copyright (C) 2024 Julian Pieles
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "editor.h"
#include <unistd.h>
#include <stdlib.h>
#include "cedfile.h"

#define LINE_NUMBERS_EN 1
#define LINE_NUMBERS_WIDTH 5
#define TITLE_BAR_ENABLED 1
#define COLORS_EN 0

/* CONSTRUCTOR */
Editor* new_Editor(CED_FILE* file) {
    Editor* editor = malloc(sizeof(Editor));
    editor->file = file;
    editor->filename = file->filename;
    editor->mode = 0;
    editor->curx = LINE_NUMBERS_EN * LINE_NUMBERS_WIDTH;
    editor->cury = TITLE_BAR_ENABLED;
    editor->x_offset = 0;
    editor->y_offset = 0;

    return editor;
}  /* new_Editor */

/* DESTRUCTOR */
void delete_Editor(Editor* editor) {
    endwin();
    free(editor->titlebar);
}  /* delete_Editor */

/* initialize ncurses screen */
void init_editor() {
    initscr();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, 1);
    if (COLORS_EN) {
        start_color();
    }
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    attron(COLOR_PAIR(2));
}  /* init_editor */

void draw_line_numbers(Editor* editor) {
    attron(A_REVERSE);
    for (int y = 1; y < LINES; y++) {
        if (y < editor->file->numlines) {
            mvprintw(y, 0, "%4d ", y + editor->y_offset);
        } else {
            mvprintw(y, 0, "     ");
        }
        if (COLS > 80 + (LINE_NUMBERS_EN * LINE_NUMBERS_WIDTH)) {  /* 80 column marker */
            move(y, 80 + (LINE_NUMBERS_EN * LINE_NUMBERS_WIDTH));
            printw(" ");
        }
    }
    attroff(A_REVERSE);
}  /* draw_line_numbers */

void quit(Editor* editor) {
    editor->running = 0;
}

void handle_command(Editor* editor) {
    printw("%d", LINES);
    attron(A_REVERSE);
    mvprintw(LINES, 5, "%20s", " ");
    printw(":");
    int ch = getch();
    while (ch != 'q') { ch = getch(); }
        move(LINES, 6);
        printw("q");
        int ch2 = getch();
        while (ch2 != KEY_ENTER && ch2 != '\n') { ch2 = getch(); }
        quit(editor);
        attroff(A_REVERSE);
}  /* handle_command */

void move_left(Editor* editor) {
    if (editor->curx > 5) {
        editor->curx--;
    } else if (editor->x_offset > 0) {
        editor->x_offset--;
    }
}  /* move_left */

void move_right(Editor* editor) {
        if (editor->curx < COLS - 1) {
            editor->curx++;
        } else if (editor->curx + editor->x_offset < COLS) {
            editor->x_offset++;
        }
}  /* move_right */

void move_down(Editor* editor) {
        int y_abs = editor->cury + editor->y_offset;

        if (editor->cury < LINES - 1 && editor->cury < editor->file->numlines) {
            editor->cury++;
        } else if (y_abs < editor->file->numlines - 1) {
            editor->y_offset++;
        }

        if (editor->curx > strlen(editor->file->text[y_abs].line) + 1) {
            editor->curx = strlen(editor->file->text[y_abs].line) + 1;
        }
}  /* move_down */

void move_up(Editor* editor) {
        int y_abs = editor->cury + editor->y_offset;

        if (editor->cury > 1) {
            editor->cury--;
        } else if (editor->y_offset > 0) {
            editor->y_offset--;
        }
        if (editor->curx > strlen(editor->file->text[y_abs].line + 1)) {
            editor->curx = strlen(editor->file->text[y_abs].line) + 1;
        }
}  /* move_up */

void set_mode(Editor* editor, int mode) {
    editor->mode = mode;
    editor->titlebar->mode = mode;
}  /* set_mode */

/* Update function used when in NORMAL mode */
void update_normal(Editor* editor) {
    char lastchar = getch();

    int prev_ch = 0;
    int timeout = 50;

    switch (lastchar) {
        case 'h': move_left(editor); break;
        case 'l': move_right(editor); break;
        case 'j': move_down(editor); break;
        case 'k': move_up(editor); break;
        case 'i': set_mode(editor, 1);
    }

    if (editor->curx < 5) editor->curx = 5;
    if (editor->cury < 1) editor->cury = 1;

    if (lastchar == 'g') {
        int next_ch = getch();
        while (next_ch != 'g') {next_ch = getch();}
            editor->cury = 1;
            editor->curx = 5;
            editor->y_offset = 0;
            move(editor->cury, editor->curx);
    }

    if (lastchar == ':') {
        handle_command(editor);
    }

    if (lastchar == 'G') {
        editor->y_offset = editor->file->numlines - LINES;
        editor->cury = LINES;
        editor->curx = 5;
        // move(editor->cury, editor->curx);
    }

    /*if (lastchar == 'a' || lastchar == 127 || lastchar == KEY_BACKSPACE) {
        if (strlen(editor->file->text[editor->cury + editor->y_offset].line) == 0) {
            remove_line(editor->file, editor->cury + editor->y_offset);
        } else if (editor->curx > 1) {
            // remove_char(editor->file->text[editor->cury + editor->y_offset], editor->curx - 2);
        }
        print_file(editor->file, 0 + editor->y_offset, LINES + editor->y_offset, editor->x_offset, editor->y_offset);
    }*/
}  /* update_normal */

/* Update function usen when in INSERT mode */
void update_insert(Editor* editor) {
    int ch = getch();
    if (ch == 27) { /* ESC_KEY */
        set_mode(editor, 0);
    }
    if (ch != 27) {
        printw("%c", ch);
        move(editor->cury, editor->curx + 1);
    }
}  /* update_insert */

void update(Editor* editor) {
    editor->titlebar->x = editor->curx;
    editor->titlebar->y = editor->cury;

    switch (editor->mode) {
        case 0: update_normal(editor); break;
        case 1: update_insert(editor); break;
    }
}  /* update */

void render(Editor* editor) {
        render_titlebar(editor->titlebar);
        
        if(LINE_NUMBERS_EN) {
            draw_line_numbers(editor);
        }

        int start = editor->y_offset;
        int end = LINES + editor->y_offset;
        int x_offset = editor->x_offset;
        int y_offset = editor->y_offset;
        print_file(editor->file, start, end, x_offset, y_offset);
        move(editor->cury, editor->curx);
        refresh();
}  /* render */

int run_editor(Editor* editor) {
    init_editor();

    editor->running = 1;

    Titlebar* titlebar = malloc(sizeof(Titlebar));
    titlebar->filename = editor->filename;
    titlebar->mode = editor->mode;
    titlebar->x = editor->curx;
    titlebar->y = editor->cury;
    titlebar->loc = editor->file->numlines;

    editor->titlebar = titlebar;

    while (editor->running) {
        update(editor);
        render(editor);
    }

    delete_Editor(editor);

    return 0;
}  /* run_editor */
