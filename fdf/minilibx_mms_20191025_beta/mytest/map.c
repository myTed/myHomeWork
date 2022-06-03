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

static int	get_column_from_file(char *path_name, t_map_info *pmap)
{
	char	buff[256];
	ssize_t	read_cnt;
	int		idx;
	int		fd;

	if ((path_name == 0) || (pmap == 0))
		return (-1);
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		return (-2);
	while (1)
	{
		read_cnt = read(fd, buff, sizeof(buff));
		if (read_cnt == 0)
			break ;
		else
		{
			idx = 0;
			while (idx < read_cnt)
			{
				if (buff[idx] == '\n')
					pmap->height++;
				idx++;
			}
		}
	}
	if (close(fd) < 0)
		return (-3);
	return (0);
}

static int is_found_color_idx(char *str)
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

/*
static void display_map(t_cordinate *pcord_arry, int colum_size, int width_size)
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
*/
static int get_width_from_file(char *file_name, t_map_info *pmap)
{
	int 	fd;
	char	*line;
	char	**width_mat_arry;
	int		idx;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-2);
	line = get_next_line(fd);
	if (line == 0)
		return (-3);
	width_mat_arry = ft_split(line, ' ');
	if (width_mat_arry == 0)
		return (-4);
	free(line);
	while (width_mat_arry[pmap->width] != 0)
		pmap->width++;
	idx = 0;
	while (width_mat_arry[idx] != 0)
	{
		free(width_mat_arry[idx]);
		idx++;
	}
	free(width_mat_arry);
	
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		free(line);
	}
	close(fd);
	return (0);
}

static int fill_cordinate_from_line(char **z_values, int col_idx, t_map_info *pmap)
{
	int	idx;
	int	color_idx;
	int color_value;
	int	widths;


	if ((z_values == 0) || (pmap == 0))
		return (-1);
	idx = 0;
	widths = pmap->width;
	while(z_values[idx] != 0)
	{
		pmap->pcord[(widths * col_idx) + idx].z = ft_atoi(z_values[idx]);
		pmap->pcord[(widths * col_idx) + idx].y = idx;
		pmap->pcord[(widths * col_idx) + idx].x = col_idx;
		color_idx = is_found_color_idx(z_values[idx]);
		if (color_idx != 0)
		{
			color_value = ft_atoi_base(z_values[idx] + col_idx + 3, "0123456789ABCDEF");
			pmap->pcord[(widths * col_idx) + idx].color = *(t_color *)&color_value;
		}
		idx++;
	}
	return (0);
}

static int	fill_cordinate_from_file(char *file_name, t_map_info *pmap)
{
	int		fd;
	char	*line;
	int		col_idx;
	char	**z_values_per_line;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-2);
	col_idx = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		z_values_per_line = ft_split(line, ' ');
		if (fill_cordinate_from_line(z_values_per_line, col_idx, pmap) < 0)
		{
			free(line);
			return (-3);
		}
		col_idx++;
		free(line);
	}
	return (0);
}

int	fill_map_data(char *file_name, t_map_info *pmap)
{
	ft_memset(pmap, 0, sizeof(t_map_info));

	if (get_column_from_file(file_name, pmap) < 0)
		return (-1);
	if (get_width_from_file(file_name, pmap) < 0)
		return (-1);
	pmap->pcord = malloc(sizeof(t_cordinate) * pmap->width * pmap->height);
	if (pmap->pcord == 0)
		return (-1);
	if (fill_cordinate_from_file(file_name, pmap) < 0)
	{
		if (pmap->pcord != 0)
			free(pmap->pcord);
		return (-1);
	}
	return (0);
}

/*
int	main(int argc, char **argv)
{
	t_map_info		map;
	
	if (argc != 2)
	{
		printf("program mapfile\n");
		exit(1);
	}
	fill_map_data(argv[1], &map);
	printf("col: %d, width: %d\n", map.height, map.width);
	display_map(map.pcord, map.height, map.width);	
	return (0);
}
*/
