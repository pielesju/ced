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
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "ced/editor.h"
#include "ced/cedfile.h"
#include "ced/commandline.h"
#include "ced/filehandler.h"

#define LINE_NUMBERS_EN 1
#define LINE_NUMBERS_WIDTH 5
#define TITLE_BAR_ENABLED 1
#define COLORS_EN 0

/* CONSTRUCTOR */
Editor* new_Editor(CED_FILE* file) {
    Editor* editor = malloc(sizeof(Editor));
    editor->file = file;
    editor->filename = file->filename;
    editor->snipboard = malloc(sizeof(char));
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
    free(editor->snipboard);
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
    char block_buffer[LINES * 8];
    block_buffer[0] = '\0';
    char *buffer_ptr = block_buffer;

    for (int y = TITLE_BAR_ENABLED; y < LINES; y++) {
        if (y < editor->file->numlines) {
            buffer_ptr += sprintf(buffer_ptr, "%4d ", y + editor->y_offset);
        } else {
            buffer_ptr += sprintf(buffer_ptr, "     ");
        }

        *buffer_ptr++ = '\n';
    }

    *buffer_ptr = '\0';

    mvaddstr(TITLE_BAR_ENABLED, 0, block_buffer);
}  /* draw_line_numbers */

void quit(Editor* editor) {
    editor->running = 0;
}

void move_left(Editor* editor) {
    if (editor->curx > 5) {
        editor->curx--;
    } else if (editor->x_offset > 0) {
        editor->x_offset--;
    }
}  /* move_left */

void move_right(Editor* editor) {
        if (editor->curx < COLS - 1 &&
           (size_t) editor->curx <
           strlen(editor->file->text[editor->cury].line) - 5) {
            editor->curx++;
        } else if (editor->curx + editor->x_offset < COLS) {
            editor->x_offset++;
        }
}  /* move_right */

void move_down(Editor* editor) {
        int y_abs = editor->cury;

        if (editor->cury < LINES - 1 &&
            editor->cury < editor->file->numlines - 1) {
            editor->cury++;
        } else if (y_abs < editor->file->numlines - 1) {
            editor->y_offset++;
        }

        if ((size_t) editor->curx >
            strlen(editor->file->text[y_abs].line) - 5) {
            editor->curx = strlen(editor->file->text[y_abs].line) - 5;
        }
}  /* move_down */

void move_up(Editor* editor) {
        int y_abs = editor->cury;

        if (editor->cury > 1) {
            editor->cury--;
        } else if (editor->y_offset > 0) {
            editor->y_offset--;
        }
        if ((size_t) editor->curx >
            strlen(editor->file->text[y_abs].line + 5)) {
            editor->curx = strlen(editor->file->text[y_abs].line) + 5;
        }
}  /* move_up */

void set_mode(Editor* editor, int mode) {
    editor->mode = mode;
    editor->titlebar->mode = mode;
}  /* set_mode */

void handle_g(Editor* editor) {
    int next_ch = getch();
    while (next_ch != 'g') {next_ch = getch();}
    editor->cury = 1;
    editor->curx = 5;
    editor->y_offset = 0;
    move(editor->cury, editor->curx);
}  /* handle_g */

void handle_d(Editor* editor) {
    int next_ch = getch();
    while (next_ch != 'd' && next_ch != 'w') {
        next_ch = getch();
    }
    if (next_ch == 'd') {  /* dd - delete line */
    strcpy(editor->snipboard, editor->file->text[editor->cury - 1].line);
        remove_line(editor->file, editor->cury - 1);
    }
    if (next_ch == 'w') {  /* dw - delete word */
        remove_word(&editor->file->text[editor->cury - 1], editor->curx - 5);
    }
}  /* handle_d */

void handle_y(Editor* editor) {
    int next_ch = getch();

    while (next_ch != 'y') {
        next_ch = getch();
    }

    if (next_ch == 'y') { /* yy - copy (yank) line */
        strcpy(editor->snipboard, editor->file->text[editor->cury - 1].line);
    }
}

void move_to_bottom(Editor* editor) {
    if (editor->file->numlines <= LINES - 2) {
        editor->cury = editor->file->numlines;
    } else {
        editor->y_offset = editor->file->numlines - LINES;
        editor->cury = LINES - 1;
    }
    editor->curx = 5;
}  /* move_to_bottom */

void insert(Editor* editor) {
    insert_line(editor->file, editor->cury);
    printw("%s", editor->snipboard);
    strcpy(editor->file->text[editor->cury].line, editor->snipboard);
}  /* insert */

/* Update function used when in NORMAL mode */
void update_normal(Editor* editor) {
    char lastchar = getch();

    switch (lastchar) {
        case 'h': move_left(editor); break;
        case 'l': move_right(editor); break;
        case 'j': move_down(editor); break;
        case 'x': remove_char(
                      &editor->file->text[editor->cury - 1],
                      editor->curx - 5);
                  break;
        case 'p': insert(editor); break;
        case 'k': move_up(editor); break;
        case 'i': set_mode(editor, 1); break;
        case 'g': handle_g(editor); break;
        case 'd': handle_d(editor); break;
        case 'y': handle_y(editor); break;
        case ':': handle_command(editor); break;
        case 'G': move_to_bottom(editor); break;
    }
}  /* update_normal */

void backspace(Editor* editor) {
    if (editor->curx > 4) {
        remove_char(
            &editor->file->text[editor->cury - 1],
            editor->curx - 6);
        move_left(editor);
    } else {
        printw("adjaoiwjw");
        remove_line(editor->file, editor->cury - 1);
        editor->cury--;
        editor->curx = strlen(editor->file->text[editor->cury].line) + 5;
    }
}

/* Update function usen when in INSERT mode */
void update_insert(Editor* editor) {
    int lastchar = getch();

    switch (lastchar) {
    case 27: set_mode(editor, 0); break;
    case KEY_BACKSPACE: backspace(editor); break;
    default: insert_char(&editor->file->text[editor->cury - 1],
             lastchar, editor->curx - 5);
             break;
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
    /* inverse colors */
    attron(A_REVERSE);
    editor->titlebar->columns = COLS;
    render_titlebar(editor->titlebar);

    if (LINE_NUMBERS_EN) {
        draw_line_numbers(editor);
    }

    /* disable inverse colors */
    attroff(A_REVERSE);

    print_file(
        editor->file,
        editor->y_offset,
        editor->y_offset + LINES,
        editor->x_offset);

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
/* editor.c */
