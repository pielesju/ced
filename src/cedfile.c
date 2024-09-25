#include "cedfile.h"

void init_file(CED_FILE *p, char *filename, int size) {
	p->text = (LINE *)malloc(size * sizeof(LINE));

	for(int i = 0; i < size; i++) {
		init_line(p->text + i);
	}

    strcpy(p->filename, filename);
	p->numlines = 0;
	p->size = size;
}

void dest_file(CED_FILE *p) {
	for(int i = 0; i < p->numlines; i++) {
		free(p->text[i].line); 
	}

	free(p->text);
}

void insert_line(CED_FILE *p, int index) {	
	if(p->numlines >= p->size) {
        expand_file(p);
    }
	
	LINE newline;
	init_line(&newline);
	newline.line[0] = '\0';
	
	for(int i = p->numlines - 1; i >= index; i--) {
		p->text[i + 1] = p->text[i];
    }

	p->text[index] = newline;
	(p->numlines)++;
}

void remove_line(CED_FILE *p, int index) {
	if( p->numlines > 1 ) {
		free(p->text[index].line);
	
		for(int i = index; i < p->numlines - 1; i++) {
			p->text[i] = p->text[i + 1];
		}

		(p->numlines)--;
	}
}

void expand_file(CED_FILE *p) {
	int newsize = p->size * 2;
	LINE *newline = malloc(newsize * sizeof(LINE));
	
	for(int i = 0; i < p->size; i++) {
		newline[i] = p->text[i];
    }

	for(int i = p->size; i < newsize; i++) {
		init_line(newline + i);
	}

	p->text = newline;
	p->size = newsize;
}

void print_file(const CED_FILE *p, int start, int end, int x_offset, int y_offset) {
	int line;
	for(int i = start, line = 0; i < p->numlines && i < end; i++, line++) {
		int start_pos = 5;
        clrtoeol();
        for(int j = x_offset; j < strlen(p->text[j].line) || j < COLS - 6; j++) {
            move(line + 1, 5 + j - x_offset);
            if(j == 85 - x_offset + 1) {
                attron(A_REVERSE);
                printw("%c", p->text[i].line[j]);
                attroff(A_REVERSE);
            } else {
                printw("%c", p->text[i].line[j]);
            }
        }
	}
    if(start < end) {
        move(line + 1, 4);   
        clrtoeol();
        move(line-1, 1);
    }
	refresh();
}
