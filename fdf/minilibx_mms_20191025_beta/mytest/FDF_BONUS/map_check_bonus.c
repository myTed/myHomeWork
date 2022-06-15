/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:37:55 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:20:21 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../gnl/ft_gnl.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int	get_next_line_until_eof(int fd);
int	get_width_from_line(int fd, t_map_info *pmap);

int	free_split(char **str)
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
			break ;
		free(line);
		pmap->height++;
	}
	return (0);
}

static int	get_width_from_file(char *file_name, t_map_info *pmap)
{
	int	fd;

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

static int	is_equal_widths_per_line(int fd, t_map_info *pmap)
{	
	char	*line;
	char	**pline;
	int		width_cnt;

	if ((fd == 0) || (pmap == 0))
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		pline = ft_split(line, ' ');
		free(line);
		if (pline == 0)
			return (-1);
		width_cnt = 0;
		while ((pline[width_cnt] != 0) && (pline[width_cnt][0] != '\n'))
			width_cnt++;
		free_split(pline);
		if (width_cnt != pmap->width)
			return (-1);
	}
	if (width_cnt == 0)
		return (-1);
	return (0);
}

int	is_valid_map_file(char *file_name, t_map_info *pmap)
{
	int	fd;

	if ((file_name == 0) || (pmap == 0))
		return (-1);
	if (get_column_from_file(file_name, pmap) < 0)
		return (-2);
	if (get_width_from_file(file_name, pmap) < 0)
		return (-3);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-4);
	if (is_equal_widths_per_line(fd, pmap) < 0)
	{
		close(fd);
		return (-5);
	}
	close(fd);
	return (0);
}
