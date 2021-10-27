#include "common.h"
#include "mark.h"
#include "map.h"
#include "change_map.h"
#include "cal_square.h"
#include "error.h"

void free_int_map(int **map)
{
	int	idx;

	idx = 0;
	while(map[idx] != NULL)
	{
		free(map[idx]);
		idx++;
	}
	free(map);
}

void free_char_map(char **map)
{
	int idx;

	idx = 0;
	while (map[idx] != NULL)
	{
		free(map[idx]);
		idx++;
	}
	free(map);
}

int main(int argc, char **argv)
{
	int 	i;
	int 	fd;
	Mark 	*M;
	char	**map;
	int		**pint_map;
	int		max_value;
	t_coordinate max_square;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			fd = open(argv[i], O_RDONLY);
			if (fd == -1)
			{
				write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
				i++;
				continue;
			}
			if ((M = check_mark_file(fd)) == NULL)
				write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
			else if (check_map_file(fd, M) == 0)
				write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
			else
			{
				close(fd);
				map = get_map(argv[i], *M);
				if (map == NULL)
				{
					write(2, MEMORY_ERROR_MSG, MEMORY_ERROR_MSG_LEN);
					exit(1);
				}
				pint_map = make_int_map(M);
				if (pint_map == NULL)
				{
					write(2, MEMORY_ERROR_MSG, MEMORY_ERROR_MSG_LEN);
					exit(1);
				}
				fill_char_map_to_int_map(map, M,pint_map);
				max_value = cal_square(M, pint_map);
				get_coordinate_max_square(M, pint_map, max_value, &max_square);
				print_max_square(M, map, &max_square);
				free_int_map(pint_map);
				free_char_map(map);
			}
			free(M);
			i++;
		}
	}
}
