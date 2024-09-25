#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "editor.h"
#include "editor_configuration.h"
#include "filehandler.h"

int main(int argc, char** argv) {
    
    CED_FILE* file = malloc(sizeof(CED_FILE));;

    if(argc > 1) {
        if(file_exists(argv[1])) {
            load_file(file, argv[1]);
        } else {
            init_file(file, argv[1], CED_FILE_SIZE);
            file->numlines = 1;
        }
    } else {
        init_file(file, "untitled.txt", CED_FILE_SIZE);
        file->numlines = 1;
    }



    Editor* editor = malloc(sizeof(Editor));
    editor->mode = 0; /* NORMAL mode */
    editor->filename = "abc";
    editor->file = file;
    editor->curx = 5;
    editor->cury = 1;
    editor->x_offset = 0;
    editor->y_offset = 0;
    int exitCode = run_editor(editor);
    free(editor);

    return exitCode;
}
