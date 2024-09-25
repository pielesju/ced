#include "editor.h"
#include <unistd.h>
#include <stdlib.h>

void init_editor() {
    initscr();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, 1);
    //scrollok(stdscr, FALSE);
    //idlok(stdscr, FALSE);
}

void draw_line_numbers(Editor* editor) {
    attron(A_REVERSE);
    for(int y = 1; y < LINES; y++) {
        if(y <= editor->file->numlines) {
            mvprintw(y, 0, "%4d ", y + editor->y_offset);
        } else {
            mvprintw(y, 0, "     ");
        }
        if(COLS > 85) { // 80 column marker
            move(y, 85);
            printw(" ");
        }
    }
    attroff(A_REVERSE);
}

void handle_command(Editor* editor) {
    move(LINES, 5);
    attron(A_REVERSE);
    printw("%20s", " ");
    printw(":");
    int ch = getch();
    while(ch != 'q') { ch = getch(); }
        move(LINES, 5);
        printw("q");
        int ch2 = getch();
        while(ch2 != KEY_ENTER && ch2 != '\n' && ch2 != 'a') { ch2 = getch(); }
        editor->running = 0;
        attroff(A_REVERSE);
    }

void move_left(Editor* editor) {
    if(editor->curx > 5) {
        editor->curx--;
    }
    else if(editor->x_offset > 0) {
        editor->x_offset--;
    }
}

void move_right(Editor* editor) {
        if(editor->curx < COLS - 1) {
            editor->curx++;
        } else if(editor->curx + editor->x_offset < COLS) {
            editor->x_offset++;
        }
}

void move_down(Editor* editor) {
        if(editor->cury < LINES - 1 && editor->cury < editor->file->numlines) {
            editor->cury++;
        } else if(editor->cury + editor->y_offset < editor->file->numlines - 1) {
            editor->y_offset++;
        }

        if(editor->curx > strlen(editor->file->text[editor->cury + editor->y_offset].line) + 1) {
            editor->curx = strlen(editor->file->text[editor->cury + editor->y_offset].line) + 1;
        }
}

void move_up(Editor* editor) {
        if(editor->cury > 1) {
            editor->cury--;
        } else if (editor->y_offset > 0) {
            editor->y_offset--;
        }
        if(editor->curx > strlen(editor->file->text[editor->cury + editor->y_offset].line + 1)) {
            editor->curx = strlen(editor->file->text[editor->cury + editor->y_offset].line) + 1;
        }
}

void update_normal(Editor* editor) {
    char lastchar = getch();

    int prev_ch = 0;
    int timeout = 50;

    switch(lastchar) {
        case 'h': move_left(editor); break;
        case 'l': move_right(editor); break;
        case 'j': move_down(editor); break;
        case 'k': move_up(editor); break;
        case 'i': editor->mode = 1;
    }

    if(editor->curx < 5) editor->curx = 5;
    if(editor->cury < 1) editor->cury = 1;

    if(lastchar == 'g') {
        int next_ch = getch();
        while(next_ch != 'g') {next_ch = getch();}
            editor->cury = 1;
            editor->curx = 5;
            editor->y_offset = 0;
            move(editor->cury, editor->curx);
    }

    if(lastchar == ':') {
        handle_command(editor);
    }

    if(lastchar == 'G') {
        editor->y_offset = editor->file->numlines - LINES;
        editor->cury = LINES;
        editor->curx = 5;
        move(editor->cury, editor->curx);
        refresh();
    }

    if(lastchar == 'a' || lastchar == 127 || lastchar == KEY_BACKSPACE) {
        if(strlen(editor->file->text[editor->cury + editor->y_offset].line) == 0) {
            remove_line(editor->file, editor->cury + editor->y_offset);
        } else if(editor->curx > 1) {
            // remove_char(editor->file->text[editor->cury + editor->y_offset], editor->curx - 2);
        }
        print_file(editor->file, 0 + editor->y_offset, LINES + editor->y_offset, editor->x_offset, editor->y_offset);
    }

}

void update_insert(Editor* editor) {
    int ch = getch();
    if(ch == 27) { // ESC
        editor->mode = 0;
    } 
    if(ch != 27) {
        printw("%c", ch);
        move(editor->cury, editor->curx + 1);
    }
}

void update(Editor* editor) {
    switch(editor->mode) {
        case 0: update_normal(editor); break;
        case 1: update_insert(editor); break;
    }
}

void render(Editor* editor, Titlebar* titlebar) {
        render_titlebar(titlebar);
        draw_line_numbers(editor);
        print_file(editor->file, 0 + editor->y_offset, LINES + editor->y_offset, editor->x_offset, editor->y_offset);
        move(editor->cury, editor->curx);
        refresh();
}

int run_editor(Editor* editor) {
    init_editor();

    editor->running = 1;
  
    Titlebar* titlebar = malloc(sizeof(Titlebar));
    titlebar->filename = editor->filename;
    titlebar->mode = editor->mode;
    titlebar->x = editor->curx;
    titlebar->y = editor->cury;
    titlebar->loc = editor->file->numlines;

    while(editor->running) {
        render(editor, titlebar);
        update(editor);
    }


    endwin();

    free(titlebar);

    return 0;
}
