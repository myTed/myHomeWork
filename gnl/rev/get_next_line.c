/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/03 21:18:09 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>
#include <time.h>
size_t	ft_strlen(const char *s)
{
	size_t	idx;

	if (s == 0)
		return (0);
	idx = 0;
	while (s[idx] != 0)
		idx++;
	return (idx);
}

void ft_memcpy(char *dest, const char *src, size_t size)
{
	size_t			idx;

	idx = 0;
	while (idx < size)
	{
		dest[idx] = src[idx];
		idx++;
	}
}

char	*ft_strdup(const char *s, size_t size)
{
	char	*str;
	size_t	idx;

	if (s == 0 || size == 0)
		return (0);
	str = NULL;
	str = malloc(size + 1);
	idx = 0;
	if (str != NULL)
	{
		while (idx < size)
		{
			str[idx] = s[idx];
			idx++;
		}
		str[idx] = 0;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2, size_t s1_len, size_t s2_len)
{
	char	*str;

	if ((s1 == 0) || (s2 == 0))
	{
		if (s1 == 0 && s2 == 0)
			return (NULL);
		else if (s1)
			return (ft_strdup(s1, s1_len));
		else
			return (ft_strdup(s2, s2_len));
	}
	str = NULL;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str != NULL)
	{
		ft_memcpy(str, s1, s1_len);
		ft_memcpy(str + s1_len, s2, s2_len);
		str[s1_len + s2_len] = 0;
	}
	return (str);
}


int	is_found_enter(char *s, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		if (s[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}

int	expand_buff(char **buff, size_t read_cnt, size_t cur_len, size_t plus_len)
{
	char	*new;

	new = malloc(sizeof(char) * (cur_len + plus_len));
	if (new == 0)
		return (0);
	ft_memcpy(new, *buff, read_cnt);
	free(*buff);
	*buff = new;
	return (1);
}



ssize_t	repeat_read(int fd, char **buff, size_t init_buff_len, size_t *total_read)
{
	ssize_t	read_cnt;
	size_t	buff_max_len;

	read_cnt = 0;
	buff_max_len = init_buff_len;
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
			if (expand_buff(buff, *total_read, buff_max_len, init_buff_len) == 0)
				return (-1);
			buff_max_len += init_buff_len;
		}
	}
}

char	*ft_read_line(int fd, char **buff, char *prev, size_t buff_max_len)
{
	size_t	read_cnt;
	char	*line;

	read_cnt = 0;
	if (repeat_read(fd, buff, buff_max_len, &read_cnt) < 0)
		return (0);
	line = ft_strjoin(prev, *buff, ft_strlen(prev), read_cnt);
	if (line == 0)
	{
		free(prev);
		return (0);
	}
	free(prev);
	return (line);
}

char	*make_line(char **cur)
{
	char	*line;
	char	*new_cur;
	size_t	idx;
	size_t	line_len;

	if (*cur == 0)
		return (0);
	line = *cur;
	idx = 0;
	line_len = ft_strlen(line);
	if (!is_found_enter(line, line_len))
		return (0);
	while(line[idx++] != '\n');
	if (idx == line_len)
		return (0);
	else
		new_cur = ft_strdup(line + idx, line_len - idx + 1);
	if (new_cur == 0)
	{
		free(line);
		*cur = 0;
		return (0);
	}
	line[idx] = 0;
	return (new_cur);
}

struct timespec begin;
struct timespec end;


char	*get_next_line(int fd)
{
	char 		*buff;
	static char	*prev;
	char		*line;
	size_t		read_buff_len;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (0);
	if (BUFFER_SIZE < 100)
		read_buff_len = 100;
	else
		read_buff_len = BUFFER_SIZE;
	buff = malloc(sizeof(char) * read_buff_len);
	if (buff == 0)
		return (0);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	line = ft_read_line(fd, &buff, prev, read_buff_len);
	//clock_gettime(CLOCK_MONOTONIC, &end);	
	prev = make_line(&line);
	free(buff);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("elapsed time : %lf\n", (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) /1000000000.0); 
	return (line);
}

int	main(void)
{
	int		fd;
	//char	*buff;
	//int		read_cnt;
	char	*str;
	fd = 0;
	/*									
	fd = open("aaa.txt", O_RDONLY);	
	if (fd == -1)
		return (-1);
	*/
	
	clock_gettime(CLOCK_MONOTONIC, &begin);
	while ((str = get_next_line(fd)) != 0)
	{
		clock_gettime(CLOCK_MONOTONIC, &end);
		printf("elapsed time : %lf\n", (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) /1000000000.0); 
		printf("%s",str);
		fflush(stdout);
		free(str);
	}
	if (fd)
		close(fd);
	return (0);
}

/*
char	*ft_read_line(int fd, char *buff, char *prev, size_t prev_cnt)
{
	ssize_t	read_cnt;
	char	*tmp;
	char	*cur;
	int		error;

	error = 0;
	tmp = 0;
	read_cnt = -1;
	while (read_cnt != 0 && error == 0)
	{
		read_cnt = ft_read(fd, buff, buff_size);
		if (read_cnt == 0)
			return (prev);
		if (read_cnt < 0)
		{
			error = 1;
			break;
		}
		tmp = ft_strdup(buff, read_cnt);
		if (tmp == 0)
		{
			error = 1;
			break;
		}
		else
			cur = ft_strjoin(prev, tmp, prev_cnt, read_cnt);
		if (cur == 0)
		{
			error = 1;
			break;
		}
		else
		{
			if (prev)
				free(tmp);
			free(prev);
			prev = cur;
			prev_cnt += read_cnt;
		}
		if (is_found_enter(cur, prev_cnt) && error == 0)
			break;
	}
	if (error)
	{
		if(tmp)
			free(tmp);
		if(prev)
			free(prev);
		return (0);
	}
	return (cur);
}
*/




