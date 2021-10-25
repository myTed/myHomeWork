#ifndef MARK_H
#define MARK_H
#include<stdbool.h>
typedef struct mark
{
	int rows;
	int cols;
	char ch[3];
} Mark;
Mark *check_mark_file(int fd);
Mark *check_mark_stdi(char *str);
#endif