/* cedline.c
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
#include "cedline.h"

void init_line(LINE* s) {
    s->size = LINE_SIZE;
    s->line = malloc(LINE_SIZE * sizeof(char));
    s->line[0] = '\0';
}  /* init_line */

void insert_char(LINE* s, char c, int index) {
    if (strlen(s->line) >= s->size - 2) {
        expand(s);
    }

    for (int i = strlen(s->line); i >= index; i--) {
        s->line[i + 1] = s->line[i];
    }

    s->line[index] = c;
}  /* insert_char */

void remove_char(LINE* s, int index) {
        for (int i = index; i < strlen(s->line); i++) {
            s->line[i] = s->line[i + 1];
        }
}  /* remove_char */

void expand(LINE *s) {
    int new_size = s->size * 2;
    char* temp = malloc(new_size * sizeof(char));
    strcpy(temp, s->line);
    free(s->line);
    s->line = temp;
    s->size = new_size;
}  /* expand */

void add_char(LINE* s, char c) {
    insert_char(s, c, strlen(s->line));
}  /* add_char */
