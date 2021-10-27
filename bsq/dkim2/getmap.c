/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:08:33 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/28 00:00:34 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "utils.h"

int	read_line_zero(int fd, t_mark *M, char *buf)
{
	int	i;

	*buf = '0';
	while (is_digit(*buf))
	{
		M->rows = M->rows * 10 + (*buf - '0');
		if (read(fd, buf, 1) < 0)
			return (0);
	}
	if (M->rows == 0)
		return (0);
	i = -1;
	while (++i < 3)
	{
		if (!is_printable(*buf))
			return (0);
		M->mark[i] = *buf;
		if (read(fd, buf, 1) < 0)
			return (0);
	}
	if (*buf != '\n' || check_overlap(M->mark[0], M->mark[1], M->mark[2]))
		return (0);
	return (1);
}

char	*read_line_first(int fd, t_mark *M, char *buf)
{
	char	*first_row;

	first_row = malloc(1);
	first_row[0] = '\0';
	if (read(fd, buf, 1) < 0)
	{
		free(first_row);
		return (NULL);
	}
	while (*buf != '\n')
	{
		if (is_mark(*buf, *M) != 0 && is_mark(*buf, *M) != 1)
		{
			free(first_row);
			return (NULL);
		}
		first_row = ft_append(first_row, *buf);
		if (read(fd, buf, 1) < 0)
		{
			free(first_row);
			return (NULL);
		}
		M->cols++;
	}
	return (first_row);
}

char	**read_line_first2(t_mark M, char *first_row)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (M.rows + 1));
	i = 0;
	while (i < M.rows)
		map[i++] = malloc(sizeof(char) * (M.cols + 1));
	map[M.rows] = NULL;
	i = 0;
	while (first_row[i])
	{
		map[0][i] = first_row[i];
		i++;
	}
	map[0][i] = '\0';
	free(first_row);
	return (map);
}

int	read_lines_left(int fd, t_mark M, char ***map, char *buf)
{
	int	i;
	int	j;

	i = 1;
	while (i < M.rows)
	{
		j = 0;
		(*map)[i] = malloc(M.cols + 1);
		(*map)[i][0] = '\0';
		if (read(fd, buf, 1) < 0)
			return (0);
		while (*buf != '\n')
		{
			if (j >= M.cols || (is_mark(*buf, M) != 0 && is_mark(*buf, M) != 1))
				return (0);
			(*map)[i][j] = *buf;
			if (read(fd, buf, 1) < 0)
				return (0);
			j++;
		}
		if (j < M.cols)
			return (0);
		i++;
	}
	return (1);
}

char	**getmap(int fd, char *buf, t_mark *t_mk)
{
	char	*temp;
	char	**map;
	int		i;

	t_mk->rows = 0;
	t_mk->cols = 0;
	if (!read_line_zero(fd, t_mk, buf))
		return (0);
	temp = read_line_first(fd, t_mk, buf);
	if (!temp)
		return (0);
	map = read_line_first2(*t_mk, temp);
	if (!map)
		return (0);
	if (!read_lines_left(fd, *t_mk, &map, buf))
	{
		i = 0;
		while (map[i] != NULL)
			free(map[i++]);
		free(map);
		return (0);
	}
	return (map);
}
