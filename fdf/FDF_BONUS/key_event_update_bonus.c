/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event_update_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:21:36 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:20:04 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"

int	make_matrix_rol_x_view(t_draw_info *pdi);
int	make_matrix_rol_y_view(t_draw_info *pdi);
int	make_matrix_rol_z_view(t_draw_info *pdi);
int	make_matrix_top_view(t_draw_info *pdi);
int	make_matrix_right_view(t_draw_info *pdi);
int	make_matrix_front_view(t_draw_info *pdi);

int	update_rol(int keycode, t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if (keycode == END_ROL_X)
	{
		if (make_matrix_rol_x_view(pdi) < 0)
			return (-1);
	}
	else if (keycode == DEL_ROL_Y)
	{
		if (make_matrix_rol_y_view(pdi) < 0)
			return (-1);
	}
	else if (keycode == PGDN_ROL_Z)
	{
		if (make_matrix_rol_z_view(pdi) < 0)
			return (-1);
	}
	return (0);
}

int	update_direction(int keycode, t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if (keycode == UP)
		pdi->down -= SCREEN_DY;
	else if (keycode == DOWN)
		pdi->down += SCREEN_DY;
	else if (keycode == LEFT)
		pdi->right -= SCREEN_DX;
	else if (keycode == RIGHT)
		pdi->right += SCREEN_DX;
	return (0);
}

int	update_scale(int keycode, t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if (keycode == SCALE_UP)
	{
		pdi->scale += 0.2;
		if (pdi->scale >= 4.0)
			pdi->scale = 4.0;
	}
	else if (keycode == SCALE_DOWN)
	{
		pdi->scale -= 0.2;
		if (pdi->scale <= -0.9)
			pdi->scale = -0.9;
	}
	return (0);
}

int	update_view(int keycode, t_draw_info *pdi)
{
	if (pdi == 0)
		return (-1);
	if (keycode == TOP_VIEW)
	{
		if (make_matrix_top_view(pdi) < 0)
			return (-1);
	}
	else if (keycode == RIGHT_VIEW)
	{
		if (make_matrix_right_view(pdi) < 0)
			return (-1);
	}
	else if (keycode == FRONT_VIEW)
	{
		if (make_matrix_front_view(pdi) < 0)
			return (-1);
	}
	return (0);
}
