#ifndef CEDFILE_H
#define CEDFILE_H

#include <ncurses.h> 
#include "cedline.h" 

#define PAGE_SIZE 1000
#define NAME_LIMIT 256

typedef struct
{
    char filename[NAME_LIMIT];
	LINE *text; // lines of text
	int numlines;
	int size; // size of array
} PAGE;

void init_page(PAGE *p, char *filename, int size);
void dest_page(PAGE *p);
void insert_line(PAGE *p, int index);
void remove_line(PAGE *p, int index);
void expand_page(PAGE *p);
void print_page(const PAGE *p, int start, int end, int x_offset, int y_offset);

#endif
