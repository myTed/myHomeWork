#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mark.h"
#include "map.h"

int main(int argc, char **argv)
{
	int 	i;
	int 	fd;
	Mark 	*M;
	char **map;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			if ((M = check_mark_file(fd)) == NULL)
				write(2, "Mark Error\n", 11);
			else if (check_map_file(fd, M) == 0)
				write(2, "MAP ERROR\n", 10);
			else
			{
				printf("NUM[%d] Valid\n", i);
				close(fd);
				map = get_map(argv[i], *M);
				int j = 0;
				while (j < M->rows)
				{
					int k = 0;
					while (k < M->cols)
					{
						printf("%c",map[j][k]);
						k++;
					}
					printf("\n");
					j++;
				}
			}
			free(M);
			i++;
		}
	}
}