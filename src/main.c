#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "editor.h"
#include "editor_configuration.h"
#include "filehandler.h"

int main(int argc, char** argv) {
    PAGE* page = malloc(sizeof(PAGE));

    printf("%d", argc);

    if(argc > 1) {
        if(file_exists(argv[1])) {
            load_file(page, argv[1]);
        }
    } else {
        if(strcmp(argv[1], "-v") == 0) {
            printf("CE - Code Editor v%s\n", VERSION);
            printf("Trivial Computing %s\n", YEAR);
            return 0;
        } else {
            printf("new file\n");
            //execl("/bin/touch", "untitled.txt", NULL);
            system("touch untitled.txt");
            load_file(page, "untitled.txt");
        }
    }



    Editor* editor = malloc(sizeof(Editor));
    editor->mode = 0; /* NORMAL mode */
    editor->filename = "abc";
    editor->page = page;
    editor->curx = 5;
    editor->cury = 1;
    editor->x_offset = 0;
    editor->y_offset = 0;
    int exitCode = run_editor(editor);
    free(editor);
    free(page);

    return exitCode;
}
