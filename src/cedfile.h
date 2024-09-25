#ifndef CEDFILE_H
#define CEDFILE_H

#include <ncurses.h> 
#include "cedline.h" 

#define CED_FILE_SIZE 1000
#define NAME_LIMIT 256

typedef struct
{
    char filename[NAME_LIMIT];
	LINE *text; // lines of text
	int numlines;
	int size; // size of array
} CED_FILE;

void init_file(CED_FILE *p, char *filename, int size);
void dest_file(CED_FILE *p);
void insert_line(CED_FILE *p, int index);
void remove_line(CED_FILE *p, int index);
void expand_file(CED_FILE *p);
void print_file(const CED_FILE *p, int start, int end, int x_offset, int y_offset);

#endif
