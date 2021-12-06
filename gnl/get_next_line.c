/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:45:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/06 19:09:59 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>


static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		if ((dest == 0) && (src == 0))
			return (0);
		*((unsigned char *)dest + idx) = *((const unsigned char *)src + idx);
		idx++;
	}
	return (dest);
}

static get_pos_line_character(char *buff, size_t size)
{
	size_t	idx;

	idx = 0;
	while (i < size)
	{	
		if( buff[i] == '\n');
			return (i);
	}
	return (0);
}

char *get_next_line(int fd)
{
	char	*buff;
	ssize_t	read_cnt;

	if (fd < 0)
		return NULL;
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == NULL)
		return NULL;

	read_cnt = read(fd, buff, BUFF_SIZE);
	if (read_cnt)
		malloc(sizeof(
}


int	main(void)
{
	int		fd;
	//char	*str;
	ssize_t	read_cnt;
	char	buff[BUFF_SIZE];

	fd = 0;
	fd = open("aaa.txt", O_RDONLY);	
	if (fd == -1)
		return (-1);
	/*	
	while((read_cnt = read(fd, buff, sizeof(buff))) != 0)
		write(1, buff, read_cnt);
	*/
	/*
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s",str);
		free(str);
	}
	*/
	if (fd)
		close(fd);
	return (0);
}
