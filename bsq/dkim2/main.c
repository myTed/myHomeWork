/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:04:06 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/28 08:14:47 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "common.h"
#include "utils.h"
#include "getmap.h"
#include "change_map.h"
#include "cal_square.h"
#include "draw_map.h"
#include "error.h"

void	clear_buffer(char *buf)
{
	while (*buf != '\n')
	{
		read(0, buf, 1);
		if (*buf == '\n')
			break ;
	}
}

void	print_err(void)
{
	write(2, MAP_ERROR_MSG, MAP_ERROR_MSG_LEN);
}

int	get_map_from_standard_input(char ***map, t_mark *ps_mark)
{
	char buffer;
	
	if ((*map = getmap(0, &buffer, ps_mark)) == NULL)
	{
		clear_buffer(&buffer);
		return (-1);
	}
	return (0);
}

int	get_map_from_file(char ***pargv, char ***pmap, int *pmap_number, t_mark *ps_mark)
{
	int		fd;
	char	buffer;
	char	**argv;
	char	**map;
	int		map_number;

	argv = *pargv;
	map = *pmap;
	map_number = *pmap_number;
	if ((fd = open(argv[map_number], O_RDONLY)) != -1)
	{
		if((map = getmap(fd, &buffer, ps_mark)) != NULL)
		{
			*pmap = map;
			close(fd);
			return (0);
		}
	}
	return (-1);
}


int	main(int argc, char **argv)
{
	int		map_number;
	char	**map;
	t_mark	s_mark;

	map_number = 1;
	if (argc < 2)
	{
		if (get_map_from_standard_input(&map, &s_mark) < 0)
			print_err();
		else
			draw_maxim_square_from_map(map, &s_mark);
	}
	else
	{
		while (map_number < argc)
		{
			if(get_map_from_file (&argv, &map, &map_number, &s_mark) < 0)
				print_err();
			else
				draw_maxim_square_from_map(map, &s_mark);
			map_number++;
		}
	}	
	return (0);
}
