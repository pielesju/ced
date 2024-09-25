#ifndef TITLEBAR_H_
#define TITLEBAR_H_

#include <ncurses.h>

typedef struct {
    char* filename;
    int mode;
    int x;
    int y;
    int loc;
} Titlebar;

void render_titlebar(Titlebar* titlebar);

#endif
