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

static int	get_column_from_file(char *file_name, t_map_info *pmap)
{
	char	*line;
	int		fd;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	pmap->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break;
		free(line);
		pmap->height++;
	}
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

static int is_equal_widths_per_line(int	fd, t_map_info *pmap)
{	
	char	*line;
	char	**pline;
	int		width_cnt;

	width_cnt = 0;
	if ((fd == 0) || (pmap == 0))
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		pline = ft_split(line , ' ');
		free(line);
		if (pline == 0)
			return (-1);
		while (pline[idx] != 0)
			width_cnt++;
		free_split(pline);
		if (width_cnt != pmap->width)
			return (-1);
	}
	if (width_cnt == 0)
		return (-1);
	return (0);
}

static int get_next_line_until_eof(int fd)
{
	char	*line;

	if (fd == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		free(line);
	}
	return (0);
}


static int get_width_from_line(int fd, t_map_info *pmap)
{
	char **width_mat_arry;

	if ((fd == -1) || (pmap == 0))	
		return (-1);
	line = get_next_line(fd);
	if (line == 0)
		return (-1);	
	width_mat_arry = ft_split(line, ' ');
	if (width_mat_arry == 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	while (width_mat_arry[pmap->width] != 0)
		pmap->width++;
	free_split(width_mat_arry);
	if (get_next_line_until_eof(fd) < 0)
		return (-1);
	return (0);
}

static int get_width_from_file(char *file_name, t_map_info *pmap)
{
	int	fd;
	int	ret;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("can't file open\n");
		return (-1);
	}
	if (get_width_from_line(fd, pmap) < 0)
	{
		close(fd);
		return (-1);
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

static int	fill_cordinate_map(int fd, t_map_info *pmap)
{
	char	*line;
	int		col_idx;
	char	**z_values_per_line;

	if ((fd == -1) || (pmap == 0))
		return (-1);
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
			return (-1);
		}
		free_split(z_values_per_line);
		free(line);
		col_idx++;
	}
	return (0);
}


int	is_valid_map_file(char *file_name, t_map_info *pmap)
{
	int	fd;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	ft_memset(pmap, 0, sizeof(t_map_info));
	if (get_column_from_file(file_name, pmap) < 0)
		return (-2);
	if (get_width_from_file(file_name, pmap) < 0)
		return (-3);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-4);
	if (is_eqaul_widths_per_line(fd, pmap) < 0)
	{
		close(fd);
		return (-5);
	}
	close(fd);
	return (0);
}


int	fill_cord_data_from_map_file(char *file_name, t_map_info *pmap)
{
	int	fd;
	int	err_status;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	err_status = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	pmap->pcord = malloc(sizeof(t_cordinate) * pmap->width * pmap->height);
	if (pmap->pcord == 0)
		err_status = 1;
	if ((fill_cordinate_map(fd, pmap) < 0) && (!err_status))
		err_status = 1;
	close(fd);
	if (err_status)
	{
		if (pmap->pcord != 0)
			free(pmap->pcord);
		return (-1);
	}
	return (0);
}
