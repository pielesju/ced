/* filehandler.c
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
#include "./filehandler.h"

int count_lines(FILE* fp) {
    char ch = '\0';
    int count = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fseek(fp, 0, SEEK_SET);
    return count;
} /* count_lines */

/* saving and loading */
void load_file(CED_FILE* file, char* filename) {
    FILE* fp = fopen(filename, "r");
    int size = count_lines(fp) * 2;
    char ch = '\0';
    int line;

    if (size < CED_FILE_SIZE) {
        size = CED_FILE_SIZE;
    }

    init_file(file, filename, size);

    if (fp == NULL) {
        file->numlines = 1;
        return;
    }

    for (line = 0; line < size && ch != EOF; line++) {
        ch = fgetc(fp);
        while (ch != '\n' && ch != EOF) {
            LINE* currline = &(file->text[line]);
            if (ch != '\t') {
                add_char(currline, ch);
            } else {
                int i;
                for (i = 0; i < TAB_WIDTH; i++) {
                    add_char(currline, ' ');
                }
            }
            ch = fgetc(fp);
        }
        file->numlines++;
    }

    fclose(fp);
} /* load_file */

void save_file(CED_FILE* file) {
    FILE* fp = fopen(file->filename, "w");
    int line, col;

    for (line = 0; line < file->numlines; line++) {
        col = 0;
        while (file->text[line].line[col] != '\0') {
            fputc(file->text[line].line[col], fp);
            col++;
        }
        fputc('\n', fp);
    }

    fclose(fp);
} /* save_file */

int file_exists(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (NULL != fp) {
        fclose(fp);
        return 1;
    }

    return 0;
} /* file_exists */
