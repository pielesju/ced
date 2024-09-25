#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "cedfile.h"

int count_lines(FILE* fp);
void load_file(CED_FILE* p, char* filename);
void save_file(CED_FILE* p);
int file_exists(char* filename);

#endif
