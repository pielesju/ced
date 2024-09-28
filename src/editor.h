/* editor.h
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
#ifndef SRC_EDITOR_H_
#define SRC_EDITOR_H_

#include <ncurses.h>
#include "./cedfile.h"
#include "./cedline.h"
#include "./titlebar.h"

typedef struct {
    int mode; /* 0=NORMAL, 1=INSERT */
    char* filename;
    CED_FILE* file;
    Titlebar* titlebar;
    char* snipboard;
    int curx;
    int cury;
    int x_offset;
    int y_offset;
    int running;
} Editor;

Editor* new_Editor(CED_FILE* file);  /* CONSTRUCTOR */
int run_editor(Editor* editor);
void quit(Editor* editor);

#endif  /* SRC_EDITOR_H_ */
