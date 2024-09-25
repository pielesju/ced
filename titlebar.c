#include "titlebar.h"

void render_titlebar(Titlebar* titlebar) {
    attron(A_REVERSE);                                  
    for(int x = 0; x < COLS; x++) {                     
        mvprintw(0, x, " ");                            
    }                                                   
    
    switch(titlebar->mode) {
        case 0: mvprintw(0, 1, "-NORMAL-"); break;
        case 1: mvprintw(0, 1, "-INSERT-"); break;
    }

    mvprintw(0, 19, titlebar->filename);                
    mvprintw(0, COLS - 19, "%d", titlebar->loc);        
    mvprintw(0, COLS - 13, "%d%% %d:%d",                
    titlebar->y - 1 / titlebar->loc * 100.0,
    titlebar->x - 5, titlebar->y - 1);      
    attroff(A_REVERSE);   
}
