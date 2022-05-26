#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "fdf.h"
#include "libft/libft.h"
#include "gnl/ft_gnl.h"
#define PATH_NAME	"test_maps/elem-col.fdf"


void	exit_err(void)
{
	printf("%s\n", strerror(errno));
	exit(1);
}


int	get_width_from_line(char **line_data)
{
	int	count;

	count = 0;
	while (line_data[count] != 0)
		count++;
	return (count);
}

int	get_column_from_file(char *path_name)
{
	char	buff[256];
	ssize_t	read_cnt;
	int		line_cnt;
	int		idx;
	int		fd;

	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		exit_err();
	line_cnt = 0;
	while (1)
	{
		read_cnt = read(fd, buff, sizeof(buff));
		if (read_cnt == 0)
			return (line_cnt);
		else
		{
			idx = 0;
			while (idx < read_cnt)
			{
				if (buff[idx] == '\n')
					line_cnt++;
				idx++;
			}
		}
	}
	close(fd);
}

int is_found_color_idx(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == ',')
			return (idx);
		idx++;
	}
	return (0);
}

void fill_cordinate_from_line(char **pline_data, int col_idx, int width_cnt, t_cordinate *pcord)
{
	int	idx;
	int	color_idx;
	int color_value;

	idx = 0;
	while(pline_data[idx] != 0)
	{
		pcord[(width_cnt * col_idx) + idx].z = ft_atoi(pline_data[idx]);
		pcord[(width_cnt * col_idx) + idx].x = idx;
		pcord[(width_cnt * col_idx) + idx].y = col_idx;
		color_idx = is_found_color_idx(pline_data[idx]);
		if (color_idx != 0)
		{
			color_value = ft_atoi_base(pline_data[idx] + col_idx + 3, "0123456789ABCDEF");
			pcord[(width_cnt * col_idx) + idx].color = *(t_color *)&color_value;
		}
		idx++;
	}
}


void display_map(t_cordinate *pcord_arry, int colum_size, int width_size)
{
	int	col_idx;
	int	width_idx;

	col_idx = 0;
	width_idx = 0;
	while (col_idx < colum_size)
	{
		width_idx = 0;
		while (width_idx < width_size)
		{
			printf("%-4d", pcord_arry[(width_size * col_idx) + width_idx].z);
			width_idx++;
		}
		printf("\n");
		col_idx++;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	char		**line_data;
	int			width_cnt;
	int			column_cnt;
	t_cordinate *pcordinate;
	
	if (argc != 2)
	{
		printf("program mapfile\n");
		exit(1);
	}
	column_cnt = get_column_from_file(argv[1]);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit_err();
	int	col_idx = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break;
		line_data = ft_split(line, ' ');
		width_cnt = get_width_from_line(line_data);	
		
		if (col_idx == 0)
		{
			pcordinate = malloc(sizeof(t_cordinate) * width_cnt * column_cnt);
			if (pcordinate == 0)
				return (1);

		}
		fill_cordinate_from_line(line_data, col_idx, width_cnt, pcordinate);	
		col_idx++;
	}
	printf("col: %d, width: %d\n", column_cnt, width_cnt);
	display_map(pcordinate, column_cnt, width_cnt);
	
	return (0);
}

