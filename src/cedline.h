#ifndef LINE_H
#define LINE_H

#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 128
#define TAB_WIDTH 4

typedef struct
{
	char *line;
	int size;
} LINE;

void init_line(LINE *s);
void insert_char(LINE *s, char c, int index);
void remove_char(LINE *s, int index);
void expand(LINE *s);
void add_char(LINE *s, char c);

#endif
