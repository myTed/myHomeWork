#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int is_printable(char c)
{
	return (c != 127 && !(c >= 9 && c<= 13));
}

int is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

char *ft_strndup(char *src, int n)
{
	int i;
	char *dest;

	dest = malloc(n);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}