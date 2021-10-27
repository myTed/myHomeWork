#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "mark.h"
#include "map.h"
#include "change_map.h"
#include "cal_square.h"
#include "error.h"

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
			if ((M = check_mark_file(fd)) == NULL)
				write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
			else if (check_map_file(fd, M) == 0)
				write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
			else
			{
				//printf("NUM[%d] Valid\n", i);
				close(fd);
				map = get_map(argv[i], *M);
				pint_map = make_int_map(M);
				if (pint_map == NULL)
				{
					write(2, "",13);
					exit(1);
				}
				fill_char_map_to_int_map(map, M,pint_map);

				max_value = cal_square(M, pint_map);
				get_coordinate_max_square(M, pint_map, max_value, &max_square);
				print_max_square(M, map, &max_square);

				free(pint_map);
			}
			free(M);
			i++;
		}
	}
}
