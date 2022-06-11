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
	int		fd;
	char	*line;

	if ((path_name == 0) || (pmap == 0))
		return (-1);
	fd = open(path_name, O_RDONLY);
	if (fd == -1)
		return (-2);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break;
		free(line);
		pmap->height++;
	}
	if (close(fd) < 0)
		return (-3);
	return (0);
}

static int	free_split(char **str)
{
	int	idx;

	idx = 0;
	if (str == 0)
		return (-1);
	while (str[idx] != 0)
	{
		free(str[idx]);
		idx++;
	}
	free(str);
	return (0);
}

static int	is_equal_width_per_line(char *file_name , t_map_info *pmap)
{
	int		fd;
	char	*line;
	char	**pline;
	int		width_cnt;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	width_cnt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		pline = ft_split(line , ' ');
		if (pline == 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		while (pline[idx] != 0)
			width_cnt++;
		free_split(pline);
		if (width_cnt != pmap->width)
			return (-1);
	}
	if (width_cnt != 0)
		return (0);
}

static int get_width_from_file(char *file_name, t_map_info *pmap)
{
	int 	fd;
	char	*line;
	char	**width_mat_arry;

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
	free_split(width_mat_arry);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		pmap->height++;
		free(line);
	}
	close(fd);
	return (0);
}

static int fill_cordinate_from_line(char **z_values, int col_idx, t_map_info *pmap)
{
	int	idx;
	int	widths;
	int	num;

	if ((z_values == 0) || (pmap == 0))
		return (-1);
	idx = 0;
	widths = pmap->width;
	while(z_values[idx] != 0)
	{
		num = ft_atoi(z_values[idx]);
		pmap->pcord[(widths * col_idx) + idx].z = num;
		pmap->pcord[(widths * col_idx) + idx].y = col_idx;
		pmap->pcord[(widths * col_idx) + idx].x = idx;
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
		free_split(z_values_per_line);
		free(line);
		col_idx++;
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

