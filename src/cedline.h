/* cedline.h
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
#ifndef SRC_CEDLINE_H_
#define SRC_CEDLINE_H_

#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 128
#define TAB_WIDTH 4

typedef struct {
    char* line;
    int size;
} LINE;

void init_line(LINE* s);
void insert_char(LINE* s, char c, int index);
void remove_char(LINE* s, int index);
void expand(LINE* s);
void add_char(LINE* s, char c);

#endif  /* SRC_CEDLINE_H_ */
