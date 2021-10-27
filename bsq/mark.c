#include "mark.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int is_mark(char c, Mark M)
{
	if (c == M.ch[0])
		return (1);
	else if (c == M.ch[1])
		return (0);
	else
		return (-1);
}

Mark *check_mark_file(int fd)
{
	Mark *M;
	int i;
	char c;

	M = malloc(sizeof(Mark));
	M->rows = 0;
	read(fd, &c, 1);
	while (is_digit(c))
	{
		M->rows = M->rows * 10 + (c - '0');
		read(fd, &c, 1);
	}
	if (M->rows < 1)
		return (NULL);
	i = 0;
	while(i < 3)
	{
		if (!is_printable(c))
			return (NULL);
		M->ch[i++] = c;
		read(fd, &c, 1);
	}
	if (c != '\n')
		return (NULL);
	return (M);
}

