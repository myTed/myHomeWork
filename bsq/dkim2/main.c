/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:04:06 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/27 21:45:17 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "getmap.h"

void	clear_buffer(int fd, char *buf);

void	print_err(int fd, char *buf);

int	main(int argc, char **argv)
{
	int		fd;
	int		map_number;
	char	buffer;
	char	**map;

	map_number = 1;
	if (argc < 2)
	{
		map = getmap(0, &buffer);
		if (map == NULL)
			print_err(0, &buffer);
		else
		{

		}
	}
	else
	{
		while (map_number < argc)
		{
			fd = open(argv[map_number], O_RDONLY);
			map = getmap(fd, &buffer);
			if (map == NULL)
				print_err(fd, &buffer);
			close(fd);
			map_number++;
		}
	}	
	return (0);
}

void	clear_buffer(int fd, char *buf)
{
	while (*buf != '\n')
	{
		read(0, buf, 1);
		if (*buf == '\n')
			break ;
	}
}

void	print_err(int fd, char *buf)
{
	clear_buffer(fd, buf);
	write(1, "map error\n", 10);
}
