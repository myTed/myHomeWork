/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:23:54 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:19:45 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include <math.h>
#include <stdlib.h>

int	set_pixel(t_img *pimg, int y, int x, t_color color)
{
	if (pimg == 0)
		return (-1);
	*(pimg->addr + (y * (pimg->size_line / (pimg->bpp / 8))) + x)
		= *(unsigned int *)&color;
	return (0);
}

int	draw_pixel_low_slope(t_img *pimg, t_draw_point *pdp, t_color col)
{
	int	tmp_x;
	int	tmp_y;
	int	middle_eval;

	if ((pimg == 0) || (pdp == 0))
		return (-1);
	tmp_x = pdp->start_x;
	tmp_y = pdp->start_y;
	middle_eval = (2 * pdp->height) - pdp->width;
	while (tmp_x != pdp->end_x)
	{
		set_pixel(pimg, tmp_y, tmp_x, col);
		if (middle_eval < 0)
			middle_eval += 2 * (pdp->height);
		else
		{
			tmp_y += pdp->del_y;
			middle_eval += 2 * (pdp->height - pdp->width);
		}
		tmp_x += pdp->del_x;
	}
	return (0);
}

int	draw_pixel_high_slope(t_img *pimg, t_draw_point *pdp, t_color col)
{
	int	tmp_x;
	int	tmp_y;
	int	middle_eval;

	if ((pimg == 0) || (pdp == 0))
		return (-1);
	tmp_x = pdp->start_x;
	tmp_y = pdp->start_y;
	middle_eval = (2 * pdp->width) - pdp->height;
	while (tmp_y != pdp->end_y)
	{
		set_pixel(pimg, tmp_y, tmp_x, col);
		if (middle_eval < 0)
			middle_eval += 2 * (pdp->width);
		else
		{
			tmp_x += pdp->del_x;
			middle_eval += 2 * (pdp->width - pdp->height);
		}
		tmp_y += pdp->del_y;
	}
	return (0);
}

int	is_over_screen_size(t_draw_point *pdp)
{
	if ((pdp->start_x < 0) || (pdp->start_x >= SCREEN_WIDTHS))
		return (1);
	if ((pdp->start_y < 0) || (pdp->start_y >= SCREEN_HEIGHTS))
		return (1);
	if ((pdp->end_x < 0) || (pdp->end_x >= SCREEN_WIDTHS))
		return (1);
	if ((pdp->end_y < 0) || (pdp->end_y >= SCREEN_HEIGHTS))
		return (1);
	return (0);
}

int	draw_line(t_img *pimg, t_draw_point *pdp, t_color col)
{
	if (pimg == 0)
		return (-1);
	if (is_over_screen_size(pdp))
		return (-1);
	pdp->width = abs(pdp->end_x - pdp->start_x);
	pdp->height = abs(pdp->end_y - pdp->start_y);
	if (pdp->end_x - pdp->start_x >= 0)
		pdp->del_x = 1;
	else
		pdp->del_x = -1;
	if (pdp->end_y - pdp->start_y >= 0)
		pdp->del_y = 1;
	else
		pdp->del_y = -1;
	if (pdp->height > pdp->width)
	{
		if (draw_pixel_high_slope(pimg, pdp, col) < 0)
			return (-1);
	}
	else
	{
		if (draw_pixel_low_slope(pimg, pdp, col) < 0)
			return (-1);
	}
	return (0);
}
