/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/09 21:43:48 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"
/*
#include <stdio.h>
#include <time.h>
*/
ssize_t	repeat_read(
	int fd,
	char **buff,
	size_t buff_len,
	size_t *total_read
){
	ssize_t	read_cnt;
	size_t	buff_max_len;

	read_cnt = 0;
	buff_max_len = buff_len;
	while (1)
	{
		read_cnt = read(fd, *buff + *total_read, BUFFER_SIZE);
		if (read_cnt == 0)
			return (0);
		if (read_cnt < 0)
			return (-1);
		*total_read += read_cnt;
		if (is_found_enter(*buff, *total_read))
			return (0);
		if (*total_read + BUFFER_SIZE > buff_max_len)
		{
			if (expand_buff(buff, *total_read, buff_max_len, buff_len) == 0)
				return (-1);
			buff_max_len += buff_len;
		}
	}
}

char	*ft_read_line(
	int fd,
	char **buff,
	t_read *pread,
	size_t buff_max_len
){
	size_t	read_cnt;
	char	*line;
	size_t	idx;
	char	*prev;

	read_cnt = 0;
	idx = 0;
	while ((idx < pread->arr_cur_len) && ((pread->parr)[idx].fd != fd))
		idx++;
	if (idx == pread->arr_cur_len)
		prev = 0;
	else
		prev = pread->parr[idx].prev;
	idx = 0;
	if (prev != 0)
		while (prev[idx] != 0)
			idx++;
	if (repeat_read(fd, buff, buff_max_len, &read_cnt) < 0)
		return (0);
	else
		line = ft_strjoin(prev, *buff, idx, read_cnt);
	if (line)
		free(prev);
	return (line);
}

char	*make_line_after_enter(char **cur)
{
	char	*prev;
	size_t	idx;
	ssize_t	enter_idx;

	if (*cur == 0)
		return (0);
	idx = 0;
	enter_idx = -1;
	while ((*cur)[idx] != 0)
	{
		if (((*cur)[idx] == '\n') && (enter_idx == -1))
			enter_idx = idx;
		idx++;
	}
	if ((enter_idx == -1) || (enter_idx == (ssize_t)(idx - 1)))
		return (0);
	prev = ft_strdup((*cur) + enter_idx + 1, idx - enter_idx - 1);
	if (prev == 0)
	{
		free((*cur));
		*cur = 0;
		return (0);
	}
	(*cur)[enter_idx + 1] = 0;
	return (prev);
}

int	save_read_info_arr(t_read *pinfo, int fd, char **prev, char *line)
{
	size_t	idx;

	if (line == 0)
		return (0);
	idx = 0;
	while ((idx < pinfo->arr_cur_len) && (pinfo->parr)[idx].fd != fd)
		idx++;
	if (idx == pinfo->arr_max)
	{
		idx = sizeof(t_fd_arr) * pinfo->arr_cur_len;
		if (expand_buff((char **)&(pinfo->parr), idx, idx,
				sizeof(t_fd_arr) * FD_BUF_MAX) == 0)
		{
			free(*prev);
			free(line);
			return (-1);
		}
		idx = pinfo->arr_cur_len;
		pinfo->arr_max += FD_BUF_MAX;
	}
	(pinfo->parr)[idx].fd = fd;
	(pinfo->parr)[idx].prev = *prev;
	if (idx == pinfo->arr_cur_len)
		pinfo->arr_cur_len++;
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static t_read	read_info;
	char			*line;
	size_t			read_buff_len;
	char			*prev;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (0);
	read_buff_len = BUFFER_SIZE;
	if (BUFFER_SIZE < 128)
		read_buff_len = 128;
	buff = malloc(sizeof(char) * read_buff_len);
	if (buff == 0)
		return (0);
	if (read_info.parr == 0)
		if (init_read_info_arr(&read_info) < 0)
			return (0);
	line = ft_read_line(fd, &buff, &read_info, read_buff_len);
	free(buff);
	prev = make_line_after_enter(&line);
	if (save_read_info_arr(&read_info, fd, &prev, line) < 0)
		return (0);
	return (line);
}

/*
int	main(void)
{
	int		fd;
	char	*str;
	
	fd = 0;
	
	fd = open("abc.txt", O_RDONLY);
	if (fd == -1)
		return (-1);

	while ((str = get_next_line(fd)) != 0)
	{
		printf("%s",str);
		fflush(stdout);
		free(str);
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
	//char	*buff;
	//int		read_cnt;
	char	*str;
	int		idx;

	fd[0] = open("aaa.txt", O_RDONLY);	
	if (fd[0] == -1)
		return (-1);
	fd[1] = open("bbb.txt", O_RDONLY);
	if (fd[1] == -1)
		return (-1);
	fd[2] = open("ccc.txt", O_RDONLY);
	if (fd[2] == -1)
		return (-1);
	idx = 0;
	while (1)
	{
		str = get_next_line(fd[idx % 3]);
		idx++;
		printf("%s",str);
		fflush(stdout);
		free(str);
	}

	idx = 0;
	while (idx < 3)
	{
		if (fd[idx])
			close(fd[idx++]);
	}
	return (0);
}
*/
