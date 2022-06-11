//#include <mlx.h>
#include "../mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include <math.h>
#include "libft/libft.h"

int draw_line(t_img *pimg, int start_y, int start_x, int end_y, int end_x, t_color color);


void set_color(t_map_info *pmap, t_view_cord *pvcord, t_color color)
{
	int	idx;

	idx = 0;
	while (idx < (pmap->width * pmap->height))
	{
		pvcord[idx].color = color;
		idx++;
	}
}


void draw_row(t_img *pimg, t_map_info *pmap, t_view_cord *pvcord)
{
	int col_idx;
	int	width_idx;
	int	idx;

	col_idx = 0;
	idx = 0;
	while (col_idx < pmap->height)
	{
		width_idx = 0;
		while (width_idx < pmap->width - 1)
		{
			draw_line(pimg, pvcord[idx].x, pvcord[idx].y, pvcord[idx +1].x, pvcord[idx + 1].y,
							pvcord[idx].color);
			idx++;
			width_idx++;
		}
		idx++;
		col_idx++;
	}
}

void draw_col(t_img *pimg, t_map_info *pmap, t_view_cord *pvcord)
{
	int	col_idx;
	int	width_idx;
	int	tmp_idx;
	int	idx;
	
	width_idx = 0;
	col_idx = 0;
	idx = 0;
	tmp_idx = 0;
	while (width_idx < pmap->width)
	{
		col_idx = 0;
		while (col_idx < pmap->height -1)
		{
			draw_line(pimg, pvcord[idx].x, pvcord[idx].y, pvcord[idx + pmap->width].x, pvcord[idx + pmap->width].y, pvcord[idx].color);
			idx += pmap->width;
			col_idx++;
		}
		idx = ++tmp_idx;
		width_idx++;
	}	
}

int clear_screen(t_draw_info *pdi)
{
	t_color color;

	color.blue = 0;
	color.green = 0;
	color.red = 0;
	color.padd = 0;
	set_color(pdi->pmap, pdi->pvcord, color);
	draw_row(pdi->pimg, pdi->pmap, pdi->pvcord);
	draw_col(pdi->pimg, pdi->pmap, pdi->pvcord);
	mlx_put_image_to_window(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr, pdi->pmlx->img_ptr, 0, 0);
	return (0);
}


int	draw_screen(t_draw_info *pdi)
{
	t_color color;
	int		idx;
	
	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		pdi->pvcord[idx].x *= (SCREEN_DX * (1.0 + pdi->scale));
		pdi->pvcord[idx].y *= (SCREEN_DY * (1.0 + pdi->scale));
		pdi->pvcord[idx].z *= SCREEN_DZ;
		pdi->pvcord[idx].x += (1000 + pdi->right);
		pdi->pvcord[idx].y += (1000 + pdi->down);
		idx++;
	}
	ft_memset(&color, 0, sizeof(t_color));
	color.green = 255;
	set_color(pdi->pmap, pdi->pvcord, color);
	draw_row(pdi->pimg, pdi->pmap, pdi->pvcord);
	draw_col(pdi->pimg, pdi->pmap, pdi->pvcord);	
	mlx_put_image_to_window(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr, pdi->pmlx->img_ptr, 0, 0);
	return (0);
}


void fill_cordinate_view(t_draw_info *pdi)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		pdi->pvcord[idx].x = pdi->pmap->pcord[idx].x - (pdi->pmap->width/2);
		pdi->pvcord[idx].y = pdi->pmap->pcord[idx].y - (pdi->pmap->height/2);
		pdi->pvcord[idx].z = pdi->pmap->pcord[idx].z;
		idx++;
	}
}



int close_window(t_draw_info *pdi)
{
	if (pid == 0)
		return (-1);
	mlx_destroy_window(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr);
	free(pdi->pvcord);
	free(pdi->pmap->pcord);
	return (0);
}


int	make_rol_x_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;
	
	if (pdi == 0)
		return (-1);
	make_matrix_rotate_x(&m_rotate, 10);
	multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
	multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
	return (0);
}

int	make_rol_y_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;

	if (pdi == 0)
		return (-1);
	make_matrix_rotate_y(&m_rotate, 10);
	multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
	multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
}

int	make_rol_z_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;

	if (pdi == 0)
		return (-1);
	make_matrix_rotate_z(&m_rotate, 10);
	multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
	multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
}

int	make_matrix_top_view(t_draw_info *pdi)
{
	t_matrix	m_top;
	t_matrix	m_unit;
		
	if (pdi == 0)
		return (-1);
	make_matrix_top_view(&m_top);
	make_unit_matrix(&m_unit);
	multiply_matrix(&m_top, &m_unit, pdi->pm_view);
	return (0);
}


int	make_matrix_right_view(t_draw_info *pdi)
{
	t_matrix	m_right;
	t_matrix	m_unit;
		
	if (pdi == 0)
		return (-1);
	make_matrix_right_view(&m_right);
	make_unit_matrix(&m_unit);
	multiply_matrix(&m_right, &m_unit, pdi->pm_view);
	return (0);
}

int	make_matrix_front_view(t_draw_info *pdi)
{
	t_matrix	m_front;
	t_matrix	m_unit;
		
	if (pdi == 0)
		return (-1);
	make_matrix_front_view(&m_front);
	make_unit_matrix(&m_unit);
	multiply_matrix(&m_front, &m_unit, pdi->pm_view);
	return (0);
}

int	key_event(int keycode, void *param)
{
	t_draw_info *pdi;

	if (param == 0)
		return (-1);
	pdi = (t_draw_info *)param;
	if (keycode == ESC)
	{
		if (close_window(pdi) < 0)
			return (-1);
		exit(0);
	}
	clear_screen(pdi);
	if (keycode == END_ROL_X)
		make_rol_x_view(pdi);
	else if (keycode == DEL_ROL_Y)
		make_rol_y_view(pdi);
	else if (keycode == PGDN_ROL_Z)
		make_rol_z_view(pdi);
	else if (keycode == UP)
		pdi->down -= SCREEN_DY;
	else if (keycode == DOWN)
		pdi->down += SCREEN_DY;
	else if (keycode == LEFT)
		pdi->right -= SCREEN_DX;
	else if (keycode == RIGHT)
		pdi->right += SCREEN_DX;
	else if (keycode == SCALE_UP)
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
	else if (keycode == TOP_VIEW)
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
	fill_cordinate_view(pdi);
	make_view_cordinate(pdi);
	draw_screen(pdi);
	return (0);
}

int	mouse_event(int button, int x, int y)
{
	printf("button : %d (%d, %d)\n",button, x, y);
	return (0);
}


int	set_pixel(t_img *pimg, int y, int x, t_color color)
{
	if (pimg == 0)
		return (-1);
	*(pimg->addr + (y * (pimg->size_line / (pimg->bpp / 8))) + x) = *(unsigned int *)&color;
	return (0);
}

int draw_line(t_img *pimg, int start_x, int start_y, int end_x, int end_y, t_color col)
{
	int	tmp_x;
	int	tmp_y;
	int	middle_eval;
	int	width;
	int	height;
	int	del_x;
	int	del_y;

	if (pimg == 0)
		return (-1);
	if (start_x < 0 || start_x >= 2000)
		return (-1);
	if (start_y < 0 || start_y >= 2000)
		return (-1);
	if (end_x < 0 || end_x >= 2000)
		return (-1);
	if (end_y < 0 || end_y >= 2000)
		return (-1);
	width = abs(end_x - start_x);
	height = abs(end_y - start_y);
	del_x = (end_x - start_x) >= 0? 1 : -1;
	del_y = (end_y - start_y) >= 0? 1: -1;
	tmp_x = start_x;
	tmp_y = start_y;
	if (height > width)
	{
		middle_eval = height - (2 * width);
		while (tmp_y != end_y)
		{
			set_pixel(pimg, tmp_y, tmp_x, col);
			if (middle_eval > 0)
			{
				middle_eval += -2 * (width);
			}
			else
			{
				tmp_x += del_x;
				middle_eval += 2 * (height - width);
			}
			tmp_y += del_y;
		}
	}
	else
	{
		middle_eval = (2 * height) - width;
		while (tmp_x != end_x)
		{
			set_pixel(pimg, tmp_y, tmp_x, col);
			if (middle_eval < 0)
			{
				middle_eval += 2 * (height);
			}
			else
			{
				tmp_y += del_y;
				middle_eval += 2 * (height - width);
			}
			tmp_x += del_x;
		}
	}
	return (0);
}


int	init_mlx_lib()
{
	min.mlx_ptr = mlx_init();
	if (min.mlx_ptr == 0)
	{
		perror("can't open connection Xwinodw");
		exit(1);
	}
	min.win_ptr = mlx_new_window(min.mlx_ptr, SCREEN_WIDHS, SCREEN_HEIGHTS, "FDF");
	if (min.win_ptr == 0)
	{
		perror("can't create new window");
		exit(1);
	}
	min.img_ptr = mlx_new_image(min.mlx_ptr, SCREEN_WIDHS, SCREEN_HEIGHTS);
	if (min.img_ptr == 0)
	{
		perror("can't create new image");
		exit(1);
	}
	t_img	img;
	img.addr = (unsigned int *)mlx_get_data_addr(min.img_ptr, &img.bpp, &img.size_line, &img.endian);
	if (img.addr == 0)
		return (-1);
}

int	main(int argc, char *argv[])
{
	t_mlx 			min;
	t_map_info 		map;
	t_view_cord 	*pvcord;

	if (argc != 2)
	{
		perror("Usage: Program filename");
		exit(1);
	}
	if (is_valid_map_file(argv[1]) < 0)
	{
		perror("map error!\n");
		exit(1);
	}
	if (fill_map_data(argv[1], &map) < 0)
		return (-1);
	pvcord = malloc(sizeof(t_view_cord) * map.width * map.height);
	if (pvcord == NULL)
		return (-1);
	
	t_draw_info 	draw_info;
	t_matrix		m_iso;
	t_matrix		m_view;
	t_matrix		m_rotate;

	ft_memset(&draw_info, 0, sizeof(t_draw_info));

	draw_info.pimg = &img;
	draw_info.pmap = &map;
	draw_info.pvcord = pvcord;
	draw_info.pmlx = &min;
	draw_info.pm_iso = &m_iso;
	draw_info.pm_view = &m_view;
	draw_info.pm_rotate = &m_rotate;

	make_matrix_isometric(&draw_info);
	make_unit_matrix(&m_rotate);
	make_unit_matrix(&m_view);
	multiply_matrix(draw_info.pm_iso, draw_info.pm_rotate, draw_info.pm_view);
	fill_cordinate_view(&draw_info);
	make_view_cordinate(&draw_info);
	draw_screen(&draw_info);

	mlx_key_hook(min.win_ptr, key_event, &draw_info);
	mlx_loop(min.mlx_ptr);
	return (0);
}
