/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:24:09 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/12 00:47:27 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int	is_found_chr(const char *s, int c, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (s[idx] == (char)c)
			return (1);
		idx++;
	}
	return (0);
}

int	read_line(int fd, char *buff, char **pstr)
{
	ssize_t	read_cnt;
	ssize_t	tmp_cnt;
	char	*tmp;

	tmp_cnt = 0;
	while (1)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		if (read_cnt == 0)
			break ;
		if (read_cnt < 0)
			return (-1);
		tmp = ft_strjoin(*pstr, buff, tmp_cnt, read_cnt);
		if (tmp == 0)
			return (-1);
		free(*pstr);
		*pstr = tmp;
		if (is_found_chr(*pstr, '\n', tmp_cnt + read_cnt))
			break ;
		tmp_cnt += read_cnt;
	}
	return (0);
}

int	add_prev_line(int fd, char **pline, t_list **pplist)
{
	char	*tmp;
	size_t	line_len;
	t_list	*plist;

	line_len = 0;
	if (*pline != 0)
		line_len = ft_strlen(*pline);
	plist = *pplist;
	while (plist != NULL)
	{
		if (plist->fd == fd)
		{
			tmp = ft_strjoin(plist->left, *pline, plist->left_len, line_len);
			if (tmp == 0)
				return (-1);
			ft_lstdel(pplist, fd);
			free(*pline);
			*pline = tmp;
			break ;
		}
		plist = plist->next;
	}
	return (0);
}

int	save_line(int fd, char **pline, t_list **pplist)
{
	size_t	line_len;
	size_t	enter_pos;
	char	*tmp;
	t_list	*new_lst;

	if (*pline == 0)
		return (0);
	line_len = ft_strlen(*pline);
	if (is_found_chr(*pline, '\n', line_len - 1) == 0)
		return (0);
	enter_pos = 0;
	while ((*pline)[enter_pos] != '\n')
		enter_pos++;
	tmp = ft_strjoin(&(*pline)[enter_pos + 1], 0, line_len - enter_pos - 1, 0);
	if (tmp == 0)
		return (-1);
	new_lst = ft_lstnew(fd, tmp, line_len - enter_pos - 1);
	if (new_lst == 0)
	{
		free(tmp);
		return (-1);
	}
	ft_lstadd_back(pplist, new_lst);
	(*pline)[enter_pos + 1] = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	static t_list	*plist;
	int				error;

	if (fd < 0)
		return (0);
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == 0)
		return (0);
	line = 0;
	error = 0;
	if (read_line(fd, buff, &line) < 0)
		error = 1;
	if (!error && (add_prev_line(fd, &line, &plist) < 0))
		error = 1;
	if (!error && (save_line(fd, &line, &plist) < 0))
		error = 1;
	if (error)
	{
		free(line);
		line = 0;
	}
	free(buff);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*str;
	int		idx;
	
	fd = open("aaa.txt", O_RDONLY);
	
	fd = 0;
	while ((str = get_next_line(fd)) != 0)
	{
		printf("%s", str);
		fflush(stdout);
		free(str);
		idx++;
	}
	
	if (fd)
		close(fd);
	
	return (0);
}
*/
/*
int	main(void)
{
	int		fd[3];
	char	*str;
	int		idx;

	fd[0] = open("aaa.txt", O_RDONLY);
	if (fd[0] < 0)
		return (-1);
	fd[1] = open("bbb.txt", O_RDONLY);
	if (fd[1] < 0)
		return (-1);
	fd[2] = open("ccc.txt", O_RDONLY);
	if (fd[2] < 0)
		return (-1);
	idx = 0;
	while (1)
	{
		str = get_next_line(fd[idx % 3]);
		printf("%s", str);
		fflush(stdout);
		free(str);
		idx++;
	}
	
	if (fd)
		close(fd);
	
	return (0);
}
*/
