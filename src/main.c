/* main.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "ced/editor.h"
#include "ced/editor_configuration.h"
#include "ced/filehandler.h"

int main(int argc, char** argv) {
    CED_FILE* file = malloc(sizeof(CED_FILE));

    /* when program is started with filename*/
    if (argc > 1) {
        if (file_exists(argv[1])) {
            load_file(file, argv[1]);
        } else {
            init_file(file, argv[1], CED_FILE_SIZE);
            file->numlines = 1;
        }
    /* when no filename is given,
     * the editor starts with an untitled.txt file*/
    } else {
        init_file(file, "untitled.txt", CED_FILE_SIZE);
        file->numlines = 1;
    }



    Editor* editor = new_Editor(file);

    /* run */
    int exitCode = run_editor(editor);

    /* clean up */
    free(editor);
    free(file);

    return exitCode;
}

