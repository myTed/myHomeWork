/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:23:47 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:16:20 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include "../libft/libft.h"
#include "../../mlx.h"
#include <math.h>

int	draw_row(t_img *pimg, t_map_info *pmap, t_view_cord *pvcord)
{
	int				idx;
	t_draw_point	dp;

	if ((pimg == 0) || (pmap == 0) || (pvcord == 0))
		return (-1);
	idx = 0;
	while (idx < (pmap->width) * (pmap->height))
	{
		dp.start_x = pvcord[idx].x;
		dp.start_y = pvcord[idx].y;
		dp.end_x = pvcord[idx + 1].x;
		dp.end_y = pvcord[idx + 1].y;
		draw_line(pimg, &dp, pvcord[idx].color);
		idx++;
		if ((idx % pmap->width) == pmap->width - 1)
			idx++;
	}
	return (0);
}

int	draw_col(t_img *pimg, t_map_info *pmap, t_view_cord *pvcord)
{	
	int				idx;
	t_draw_point	dp;

	if ((pimg == 0) || (pmap == 0) || (pvcord == 0))
		return (-1);
	idx = 0;
	while (idx < (pmap->width) * (pmap->height - 1))
	{
		dp.start_x = pvcord[idx].x;
		dp.start_y = pvcord[idx].y;
		dp.end_x = pvcord[idx + pmap->width].x;
		dp.end_y = pvcord[idx + pmap->width].y;
		draw_line(pimg, &dp, pvcord[idx].color);
		idx++;
	}
	return (0);
}

int	set_color(t_map_info *pmap, t_view_cord *pvcord, t_color color)
{
	int	idx;

	if ((pmap == 0) || (pvcord == 0))
		return (-1);
	idx = 0;
	while (idx < (pmap->width * pmap->height))
	{
		pvcord[idx].color = color;
		idx++;
	}
	return (0);
}

int	clear_screen(t_draw_info *pdi)
{
	t_color	color;

	if (pdi == 0)
		return (-1);
	color.blue = 0;
	color.green = 0;
	color.red = 0;
	color.padd = 0;
	set_color(&pdi->map, pdi->pvcord, color);
	if (draw_row(&pdi->img, &pdi->map, pdi->pvcord) < 0)
		return (-1);
	if (draw_col(&pdi->img, &pdi->map, pdi->pvcord) < 0)
		return (-1);
	mlx_put_image_to_window(pdi->mlx.mlx_ptr, pdi->mlx.win_ptr,
		pdi->mlx.img_ptr, 0, 0);
	return (0);
}

int	draw_screen(t_draw_info *pdi)
{
	t_color	color;
	int		idx;

	if (pdi == 0)
		return (-1);
	idx = 0;
	while (idx < pdi->map.width * pdi->map.height)
	{
		pdi->pvcord[idx].x *= (SCREEN_DX * (1.0 + pdi->scale));
		pdi->pvcord[idx].y *= (SCREEN_DY * (1.0 + pdi->scale));
		pdi->pvcord[idx].x += (1000 + pdi->right);
		pdi->pvcord[idx].y += (1000 + pdi->down);
		idx++;
	}
	ft_memset(&color, 0, sizeof(t_color));
	color.green = 255;
	set_color(&pdi->map, pdi->pvcord, color);
	if (draw_row(&pdi->img, &pdi->map, pdi->pvcord) < 0)
		return (-1);
	if (draw_col(&pdi->img, &pdi->map, pdi->pvcord) < 0)
		return (-1);
	mlx_put_image_to_window(pdi->mlx.mlx_ptr, pdi->mlx.win_ptr,
		pdi->mlx.img_ptr, 0, 0);
	return (0);
}
