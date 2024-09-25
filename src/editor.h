#ifndef EDITOR_H_
#define EDITOR_H_

#include <ncurses.h>
#include "cedfile.h"
#include "cedline.h"
#include "titlebar.h"

typedef struct {
    int mode; /* 0=NORMAL, 1=INSERT */
    char* filename;
    PAGE* page;
    int curx;
    int cury;
    int x_offset;
    int y_offset;
    int running;
} Editor;

int run_editor(Editor* editor);

#endif
