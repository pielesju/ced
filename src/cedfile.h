/* cedfile.h
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
#ifndef SRC_CEDFILE_H_
#define SRC_CEDFILE_H_

#include <ncurses.h>
#include "cedline.h"

#define CED_FILE_SIZE 1000
#define NAME_LIMIT 256

typedef struct {
    char filename[NAME_LIMIT];
    LINE *text;  /* lines of text */
    int numlines;  /* number of lines in text */
    int size;
} CED_FILE;

void init_file(CED_FILE* file, char* filename, int size);
void dest_file(CED_FILE* file);
void insert_line(CED_FILE* file, int index);
void remove_line(CED_FILE* file, int index);
void expand_file(CED_FILE* file);
void print_file(const CED_FILE* file, int start, int end,
                int x_offset, int y_offset);

#endif  /* SRC_CEDFILE_H_ */
