/* commandline.c
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
#include "./commandline.h"
#include "./editor.h"
#include "./filehandler.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void quit_command(Editor* editor) {
    editor->mode = 0;
    clrtoeol();
}

void handle_command(Editor* editor) {
    attron(A_REVERSE);

    int x = 5; /* start cursor x position */

    mvprintw(LINES - 1, x, "%*s", COLS, " "); /* add negative line */
    mvaddstr(LINES - 1, x, ":"); /* add command start */

    int ch = getch();

    char command_buffer[256];
    int buffer_index = 0;

    while (ch != KEY_ENTER && ch != '\n') {
        ch = getch();
        /* exit command mode when pressing ESC */
        if (ch == 27) {
            quit_command(editor);
            return;
        }

        if (isprint(ch) && buffer_index < sizeof(command_buffer) - 1) {
            command_buffer[buffer_index++] = ch;
            command_buffer[buffer_index] = '\0';

            mvprintw(LINES - 1, x + 1 + buffer_index, "%c", ch);
            refresh();
        }
    }

    if (strcmp(command_buffer, "q") == 0) {
        quit(editor);
    } else if(strcmp(command_buffer, "wq") == 0) {
        save_file(editor->file);
    } else {
        mvprintw(LINES - 1, 5,
                 "Command Not Found: %s", command_buffer);
        ch = getch();
        if (ch == 27) {
            quit_command(editor);
            return;
        }
    }

    attroff(A_REVERSE);
}  /* handle_command */
