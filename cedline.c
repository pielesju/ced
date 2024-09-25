#include "cedline.h"

void init_line(LINE *s) {
	s->size = LINE_SIZE;
	s->line = (char *)malloc(LINE_SIZE * sizeof(char));
    s->line[0] = '\0';
}

void insert_char(LINE *s, char c, int index) {
	if(strlen(s->line) >= s->size - 2){
        expand(s);
    }

	for(int i = strlen(s->line); i >= index; i--) {
		s->line[i + 1] = s->line[i];
    }

	s->line[index] = c;
}

void remove_char(LINE *s, int index) {
		int i;
		int len = strlen(s->line);
		for(i = index; i < len; i++)
			s->line[i] = s->line[i + 1];
}

void expand(LINE *s) {
	int new_size = s->size * 2;
	char *temp = (char *)malloc(new_size * sizeof(char));
	strcpy(temp, s->line);
	free(s->line);
	s->line = temp;
	s->size = new_size;	
}

void add_char(LINE *s, char c) {
    insert_char(s, c, strlen(s->line));
}
