/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_handler_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:23:58 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:19:55 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include "../../mlx.h"
#include <stdlib.h>

int	update_rol(int keycode, t_draw_info *pdi);
int	update_direction(int keycode, t_draw_info *pdi);
int	update_scale(int keycode, t_draw_info *pdi);
int	update_view(int keycode, t_draw_info *pdi);
int	clear_screen(t_draw_info *pdi);
int	draw_screen(t_draw_info *pdi);

int	close_window(t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	mlx_destroy_window(pdi->mlx.mlx_ptr, pdi->mlx.win_ptr);
	free(pdi->pvcord);
	free(pdi->map.pcord);
	return (0);
}

int	switch_key(int code, t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if ((code == END_ROL_X) || (code == DEL_ROL_Y) || (code == PGDN_ROL_Z))
	{
		if (update_rol(code, pdi) < 0)
			return (-1);
	}
	else if ((code == UP) || (code == DOWN) || (code == LEFT)
		|| (code == RIGHT))
	{
		if (update_direction(code, pdi) < 0)
			return (-1);
	}
	else if (code == SCALE_UP || (code == SCALE_DOWN))
	{
		if (update_scale(code, pdi) < 0)
			return (-1);
	}
	else if (code == TOP_VIEW || (code == RIGHT_VIEW) || (code == FRONT_VIEW))
	{
		if (update_view(code, pdi) < 0)
			return (-1);
	}
	return (0);
}

int	key_event(int keycode, void *param)
{
	t_draw_info	*pdi;

	if (param == 0)
		return (-1);
	pdi = (t_draw_info *)param;
	if (keycode == ESC)
	{
		if (close_window(pdi) < 0)
			return (-1);
		exit(0);
	}
	if (clear_screen(pdi) < 0)
		return (-1);
	if (switch_key(keycode, pdi) < 0)
		return (-1);
	if (make_view_cordinate(pdi) < 0)
		return (-1);
	if (draw_screen(pdi) < 0)
		return (-1);
	return (0);
}
