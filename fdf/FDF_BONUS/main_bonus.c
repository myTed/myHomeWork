/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:23:33 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 15:37:47 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../include/ft_fdf.h"
#include "../libft/libft.h"

int	init_mlx_lib(t_mlx *pmin, t_img *pimg)
{
	if (pmin == 0)
		return (-1);
	pmin->mlx_ptr = mlx_init();
	if (pmin->mlx_ptr == 0)
		return (-1);
	pmin->win_ptr = mlx_new_window(pmin->mlx_ptr, SCREEN_WIDTHS,
			SCREEN_HEIGHTS, "FDF");
	if (pmin->win_ptr == 0)
		return (-1);
	pmin->img_ptr = mlx_new_image(pmin->mlx_ptr, SCREEN_WIDTHS,
			SCREEN_HEIGHTS);
	if (pmin->img_ptr == 0)
	{
		mlx_destroy_window(pmin->mlx_ptr, pmin->win_ptr);
		return (-1);
	}
	pimg->addr = (unsigned int *)mlx_get_data_addr(pmin->img_ptr, &pimg->bpp,
			&pimg->size_line, &pimg->endian);
	if (pimg->addr == 0)
	{
		mlx_destroy_window(pmin->mlx_ptr, pmin->win_ptr);
		return (-1);
	}
	return (0);
}

int	malloc_cordinate(t_draw_info *pdi)
{
	t_view_cord	*ptmp_vcord;
	t_cordinate	*ptmp_cord;

	ptmp_cord = malloc(sizeof(t_cordinate) * pdi->map.width * pdi->map.height);
	if (ptmp_cord == 0)
		return (-1);
	pdi->map.pcord = ptmp_cord;
	ptmp_vcord = malloc(sizeof(t_view_cord) * pdi->map.width * pdi->map.height);
	if (ptmp_vcord == 0)
		return (-1);
	pdi->pvcord = ptmp_vcord;
	return (0);
}

int	free_exit(t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if (pdi->pvcord)
		free(pdi->pvcord);
	if (pdi->map.pcord)
		free(pdi->map.pcord);
	exit(0);
}

int	err_exit(char *err_msg)
{
	if (err_msg == 0)
		return (-1);
	write(2, err_msg, ft_strlen(err_msg));
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_draw_info		draw_info;
	int				err_status;

	if (argc != 2)
		err_exit("Usage: program mapfile\n");
	ft_memset(&draw_info, 0, sizeof(t_draw_info));
	if (is_valid_map_file(argv[1], &draw_info.map) < 0)
		err_exit("Map Error!\n");
	err_status = 0;
	if ((malloc_cordinate(&draw_info) < 0) && (!err_status))
		err_status = 1;
	if ((fill_cord_from_map_file(argv[1], &draw_info.map) < 0) && (!err_status))
		err_status = 1;
	if ((init_mlx_lib(&draw_info.mlx, &draw_info.img) < 0) && (!err_status))
		err_status = 1;
	if (project_map(&draw_info) < 0 && (!err_status))
		err_status = 1;
	if (err_status)
	{
		if (free_exit(&draw_info) < 0)
			exit(1);
	}
	mlx_key_hook(draw_info.mlx.win_ptr, key_event, &draw_info);
	mlx_loop(draw_info.mlx.mlx_ptr);
	return (0);
}
