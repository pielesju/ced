/* cedfile.c
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
#include "cedfile.h"

void init_file(CED_FILE *p, char *filename, int size) {
    p->text = malloc(size * sizeof(LINE));

    for (int i = 0; i < size; i++) {
        init_line(p->text + i);
    }

    strcpy(p->filename, filename);
    p->numlines = 0;
    p->size = size;
}  /* init_file */

void dest_file(CED_FILE *p) {
    for (int i = 0; i < p->numlines; i++) {
        free(p->text[i].line);
    }

    free(p->text);
}  /* dest_file */

void insert_line(CED_FILE *p, int index) {
    if (p->numlines >= p->size) {
        expand_file(p);
    }

    LINE newline;
    init_line(&newline);
    newline.line[0] = '\0';

    for (int i = p->numlines - 1; i >= index; i--) {
        p->text[i + 1] = p->text[i];
    }

    p->text[index] = newline;
    (p->numlines)++;
}  /* insert_line */

void remove_line(CED_FILE* p, int index) {
    if ( p->numlines > 1 ) {
        free(p->text[index].line);

        for (int i = index; i < p->numlines - 1; i++) {
            p->text[i] = p->text[i + 1];
        }

        (p->numlines)--;
    }
}  /* remove_line */

void expand_file(CED_FILE *p) {
    int newsize = p->size * 2;
    LINE *newline = malloc(newsize * sizeof(LINE));

    for (int i = 0; i < p->size; i++) {
        newline[i] = p->text[i];
    }

    for (int i = p->size; i < newsize; i++) {
        init_line(newline + i);
    }

    p->text = newline;
    p->size = newsize;
}  /* expand_file */

void print_file(const CED_FILE* file, int start, int end,
                int x_offset, int y_offset) {
    int line = 0;
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1));
    for (int i = start, line = 0; i < file->numlines && i < end; i++, line++) {
        int start_pos = 5;
        clrtoeol();
        int linelength = strlen(file->text[i].line);
        //for (int j = x_offset; j < linelength || j < COLS - 6; j++) {
        char hline[linelength + 1 * 2];
        for (int j = x_offset; j < linelength && j < x_offset + COLS - 6; j++) {
            hline[j - x_offset] = file->text[i].line[j];
            

            /*move(line + 1, 5 + j - x_offset);
            if (j == 85 - x_offset) {
                attron(A_REVERSE);
                printw("%c", file->text[i].line[j]);
                attroff(A_REVERSE);
            } else {
                printw("%c", file->text[i].line[j]);
            }*/
        }
        move(line + 1, 5);
        printw("%s", hline);
    }
    if (start < end) {
        move(line + 1, 4);
        clrtoeol();
        move(line-1, 1);
    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    refresh();
}  /* print_file */
