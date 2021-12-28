/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/28 02:03:33 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdio.h>




/*
char	*ft_read_line(int fd, char *buff, char **buff_newline, ssize_t *newline_len)
{
	ssize_t	read_cnt;
	char	*tmp;

	read_cnt = read(fd, buff, BUFFER_SIZE);
	*newline_len += read_cnt;
	tmp = malloc(sizeof(char) * (*newline_len));
	if (tmp == 0)
		return (0);
	ft_memcpy(tmp, *buff_newline, *newline_len - read_cnt);
	ft_memcpy(tmp + *newline_len - read_cnt, buff, read_cnt);
	free(*buff_newline);
	*buff_newline = tmp;
	if (!is_found_newline(buff, read_cnt))
	{
		if (!ft_read_line(fd, buff, buff_newline, newline_len))
		{
			free(*buff_newline);
			return (0);
		}
	}
	return (*buff_newline);
}
*/

size_t	ft_strlen(char *str)
{
	size_t	idx;

	if (str == 0)
		return (0);
	idx = 0;
	while (str[idx] != 0)
		idx++;
	return (idx);
}


int	is_need_to_split(char *buff, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		if ((buff[idx] == '\n') && (idx < size - 1))
			return (1);
		idx++;
	}
	return (0);
}

int get_pos_newline(char *buff, size_t buff_size)
{
	size_t idx;
	
	idx = 0;
	while (idx < buff_size)
	{
		if (buff[idx] == '\n')
			return (idx);
		idx++;
	}
	return (0);
}



void ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	idx;

	if (dest == 0 || src == 0 || size == 0)
		return ;
	idx = 0;
	while (idx < size)
	{
		*((char *)dest + idx) = *((const char *)src + idx);
		idx++;
	}
}


char	*split_line(char *read_buff, char **buff, size_t size)
{
	size_t	idx;
	char	*return_line;
	char	*tmp;

	idx = get_pos_newline(*buff, size);
	return_line = malloc(sizeof(char) * (idx + 2));
	ft_memcpy(return_line, *buff, idx + 1);
	return_line[idx + 1] = 0;
	tmp = malloc(sizeof(char) * (size - idx));
	ft_memcpy(tmp, *buff + idx + 1, (size - idx - 1));
	tmp[size - idx - 1] = 0;
	if (read_buff != *buff)
		free(*buff);
	*buff = tmp;
	return (return_line);
}

char	*merge_line(char *src1, int	size1, char *src2, int size2)
{
	char *buff;
	
	if ((size1 == 0) && (size2 == 0))
		return (0);
	buff = malloc(sizeof(char) * (size1 + size2 + 1));
	if (buff == 0)
		return (0);
	ft_memcpy(buff, src1, size1 );
	ft_memcpy(buff + size1, src2, size2);
	buff[size1 + size2] = 0;
	free(src1);
	return (buff);
}

char	*ft_read_line(int fd, char *buff, char **remain, size_t remain_size)
{
	ssize_t	read_cnt;
	char	*return_line;

	read_cnt = read(fd, buff, BUFFER_SIZE);
	if (read_cnt < 0)
		return (0);
	if (read_cnt == 0 && *remain == 0)
		return (0);
	else if (read_cnt == 0 && *remain != 0)
	{	
		if (is_need_to_split(*remain, remain_size))
		{
			return_line = split_line(buff, remain, remain_size);
			return (return_line);
		}
		else
		{
			return_line = *remain;
			*remain = 0;
			return (return_line);
		}
	}
	else if (read_cnt != 0 && *remain == 0)
	{
		if (is_need_to_split(buff, read_cnt))
		{
			return_line = split_line(buff, &buff, read_cnt);
			*remain = merge_line(buff, ft_strlen(buff), *remain, 0);
			return (return_line);
		}
		else
		{
			*remain = merge_line(*remain, 0, buff, read_cnt);
			remain_size = read_cnt;
			if (buff[read_cnt - 1] == '\n')
			{
				return_line = *remain;
				*remain = 0;
				return (return_line);
			}
			else
				return (ft_read_line(fd, buff, remain, remain_size));
		}
	}
	else
	{
		*remain = merge_line(*remain, remain_size, buff, read_cnt);
		remain_size = read_cnt + remain_size;

		if (is_need_to_split(*remain, remain_size))
		{
			return_line = split_line(buff, remain, remain_size);
			return (return_line);
		}
		else 
		{
			if ((*remain)[remain_size - 1] == '\n')
			{
				return_line = *remain;
				*remain = 0;
				return (return_line);
			}
			else
				return (ft_read_line(fd, buff, remain, remain_size));
		}
	}
}

/*
void save_lines(t_endline_arry *parry, char *str, size_t size)
{
	t_endline endline;


}
*/


char	*get_next_line(int fd)
{
	static char 	*str;
	char 			*buff;
	char			*new_line;
	//static 	t_endline_arry endline_arry;

	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == 0)
		return (0);
	new_line = ft_read_line(fd, buff, &str, ft_strlen(str));
	free(buff);
	//save_lines(&endline_arry, str, str_size);
	return (new_line);
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

