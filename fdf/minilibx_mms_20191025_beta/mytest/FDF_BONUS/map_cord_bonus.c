/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cord_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:46:16 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:20:29 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/ft_fdf.h"
#include "../libft/libft.h"
#include "../gnl/ft_gnl.h"

int	free_split(char **str);

int	get_next_line_until_eof(int fd)
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

int	get_width_from_line(int fd, t_map_info *pmap)
{
	char	**width_mat_arry;
	char	*line;

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
	while ((width_mat_arry[pmap->width] != 0)
		&& (width_mat_arry[pmap->width][0] != '\n'))
		pmap->width++;
	free_split(width_mat_arry);
	if (get_next_line_until_eof(fd) < 0)
		return (-1);
	return (0);
}

static int	fill_cordinate_from_line(
				char **z_values,
				int col_idx,
				t_map_info *pmap
				){
	int	idx;
	int	widths;
	int	num;

	if ((z_values == 0) || (pmap == 0))
		return (-1);
	idx = 0;
	widths = pmap->width;
	while (z_values[idx] != 0)
	{
		if (z_values[idx][0] == '\n')
		{
			idx++;
			continue ;
		}
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

int	fill_cord_from_map_file(char *file_name, t_map_info *pmap)
{
	int	fd;
	int	err_status;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	err_status = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (fill_cordinate_map(fd, pmap) < 0)
		err_status = 1;
	close(fd);
	if (err_status)
		return (-1);
	return (0);
}
