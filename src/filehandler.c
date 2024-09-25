#include "filehandler.h"

int count_lines(FILE *fp)
{
	char ch = '\0';
	int count = 0;
	while((ch = fgetc(fp)) != EOF)
		if( ch == '\n' )
			count++;

    fseek(fp, 0, SEEK_SET); // go to beginning of file
	return count;
} // count_lines

/* saving and loading */
void load_file(CED_FILE *p, char *filename)
{
	FILE *fp = fopen(filename, "r");
	int size = count_lines(fp) * 2;
	char ch = '\0';
	int line;

    if(size < CED_FILE_SIZE)
        size = CED_FILE_SIZE;

	init_file(p, filename, size);

    if(fp == NULL) // file doesn't exist yet. don't bother reading
    {
        p->numlines = 1;
        return;
    }


    for(line = 0; line < size && ch != EOF; line++)
    {
        ch = fgetc(fp);
        while(ch != '\n' && ch != EOF)
        {
            LINE *currline = &(p->text[line]);
            if(ch != '\t')
            {
                add_char(currline, ch);
            }
            else // tab. add 4 spaces instead
            {
                int i;
                for(i = 0; i < TAB_WIDTH; i++)
                {
                    add_char(currline, ' ');
                }
            }
            ch = fgetc(fp);
        }
        p->numlines++;
    }

	fclose(fp);

} // load_file

void save_file(CED_FILE *p)
{
	FILE *fp = fopen(p->filename, "w");
	int line, col;

	for(line = 0; line < p->numlines; line++)
	{
		col = 0;
		while(p->text[line].line[col] != '\0')
		{
			fputc(p->text[line].line[col], fp);
			col++;
		}
		fputc('\n', fp);
	}

	fclose(fp);

} // save_file

int file_exists(char* filename) {
    FILE* fp = fopen(filename, "r");
    if(NULL != fp) {
        fclose(fp);
        return 1;
    }

    return 0;
}
