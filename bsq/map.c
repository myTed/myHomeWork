#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "mark.h"
#include "utils.h"

int check_first_line(int fd, Mark *M)
{
	int cols;
	char c;

	cols = 0;
	read(fd, &c, 1);
	while (c != '\n')
	{
		if (is_mark(c, *M) == -1)
			return (0);
		cols++;
		read(fd, &c, 1);
	}
	M->cols = cols;
	return (cols);
}

int check_each_line(char *str, Mark M)
{
	while (*str != '\n')
	{
		if (is_mark(*str, M) == -1)
			return (0);
		str++;
	}
	return (1);
}

int check_whole_line(int fd, Mark M)
{
	char *temp_buf;
	int i;

	i = 1;
	while (i < M.rows)
	{
		temp_buf = malloc(M.cols + 2);
		read(fd, temp_buf, M.cols + 1);
		temp_buf[M.cols + 1] = '\0';
		if (!check_each_line(temp_buf, M))
			return (0);
		free(temp_buf);
		i++;
	}
	return (1);
}

int check_map_file(int fd, Mark *M)
{
	if (check_first_line(fd, M) == 0)
	{
		close(fd);
		return (0);
	}
	if (check_whole_line(fd, *M) == 0)
	{
		close(fd);
		return(0);
	}
	close(fd);
	return (1);
}

char **get_map(char *filename, Mark M)
{
	int fd;
	int i;
	int c;
	char **charmap;

	charmap = malloc(sizeof(char *) * M.rows);
	c = 0;
	fd = open(filename, O_RDONLY);
	while (c != '\n')
		read(fd, &c, 1);
	i = 0;
	while(i < M.rows)
	{
		charmap[i] = malloc(M.cols + 1);
		read(fd, charmap[i], M.cols + 1);
		i++;
	}
	close(fd);
	return (charmap);
}