#include <mlx.h>
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
/*
int	iso_metric(t_draw_info *pdi)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		pdi->pvcord[idx].x = pdi->prcord[idx].x;
		pdi->pvcord[idx].y = pdi->prcord[idx].y;
		pdi->pvcord[idx].z = pdi->prcord[idx].z;

		rotate_z(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), -45);
		idx++;
	}
	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		rotate_x(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 90 + 35.2643897);
		idx++;
	}		
	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		rotate_z(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 180);
		idx++;
	}
	return (0);
}
*/
int iso_metric2(t_draw_info *pdi)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;
	int		idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		tmp_x = pdi->prcord[idx].x;
		tmp_y = pdi->prcord[idx].y;
		tmp_z = pdi->prcord[idx].z;

		pdi->pvcord[idx].x = (tmp_x * -0.70710) + (0.70710 * tmp_y);
		pdi->pvcord[idx].y = (0.408248 * tmp_x) +(0.408248 * tmp_y) + (0.816496 * tmp_z);
		pdi->pvcord[idx].z = (-0.5777350 *tmp_x) + (-0.577350 * tmp_y) + (-0.577350 * tmp_z);
		idx++;
	}
	return (0);
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
		idx++;
	}
	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		pdi->pvcord[idx].x += (1000 + pdi->right);
		pdi->pvcord[idx].y += (1000 + pdi->down);
		idx++;
	}
	color.green = 255;
	color.red = 0;
	color.blue = 0;
	color.padd = 0;
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
		pdi->pvcord[idx].x = pdi->pmap->pcord[idx].x - (pdi->pmap->height/2);
		pdi->pvcord[idx].y = pdi->pmap->pcord[idx].y - (pdi->pmap->width/2);
		pdi->pvcord[idx].z = pdi->pmap->pcord[idx].z;
		idx++;
	}
}

int	key_event(int keycode, void *param)
{
	t_draw_info *pdi;

	pdi = (t_draw_info *)param;
	if (keycode == ESC)
	{

		mlx_destroy_image(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr);
		mlx_destroy_window(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr);
		free(pdi->pvcord);
		exit(0);
	}
	clear_screen(pdi);

	if (keycode == END_ROL_X)
	{
		t_matrix	m_rotate;

		make_matrix_rotate_x(&m_rotate, -10);
		multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
		multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
		printf("rotate x\n");
	}
	else if (keycode == DEL_ROL_Y)
	{
		t_matrix	m_rotate;

		make_matrix_rotate_y(&m_rotate, -10);
		multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
		multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
		printf("rotate y\n");
	}
	else if (keycode == PGDN_ROL_Z)
	{
		t_matrix	m_rotate;

		make_matrix_rotate_z(&m_rotate, -10);
		multiply_matrix(pdi->pm_rotate, &m_rotate, pdi->pm_rotate);
		multiply_matrix(pdi->pm_iso, pdi->pm_rotate, pdi->pm_view);
		printf("rotate z\n");
	}
	else if (keycode == UP)
	{
		pdi->down -= SCREEN_DY;
	}
	else if (keycode == DOWN)
	{
		pdi->down += SCREEN_DY;
	}
	else if (keycode == LEFT)
	{
		pdi->right -= SCREEN_DX;
	}
	else if (keycode == RIGHT)
	{
		pdi->right += SCREEN_DX;
	}
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
		t_matrix	m_top;
		t_matrix	m_unit;
		make_matrix_top_view(&m_top);
		init_matrix(&m_unit);
		multiply_matrix(&m_top, &m_unit, pdi->pm_view);
	}
	else if (keycode == RIGHT_VIEW)
	{
		t_matrix	m_right;
		t_matrix	m_unit;
		make_matrix_right_view(&m_right);
		init_matrix(&m_unit);
		multiply_matrix(&m_right, &m_unit, pdi->pm_view);
	}
	else if (keycode == FRONT_VIEW)
	{
		t_matrix	m_front;
		t_matrix	m_unit;
		make_matrix_front_view(&m_front);
		init_matrix(&m_unit);
		multiply_matrix(&m_front, &m_unit, pdi->pm_view);
	}
	fill_cordinate_view(pdi);
	make_view_cordinate(pdi);
	draw_screen(pdi);	
	printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_event(int button, int x, int y)
{
	printf("button : %d (%d, %d)\n",button, x, y);
	return (0);
}

int	expose_event(void *param)
{
	t_mlx	*pmlx;
	static	int x;

	pmlx = (t_mlx *)param;

	if (x == 0)
	{
		mlx_string_put(pmlx->mlx_ptr, pmlx->win_ptr, 300, 300, 0, "resize!!");
		x++;
	}
	else
	{
		mlx_string_put(pmlx->mlx_ptr, pmlx->win_ptr, 300, 300, 0, "asdjfklasjdkf");
		x = 0;
	}
	printf("expose cnt : %d\n", x);
	return (0);
}

int	close_event(void)
{
	exit(0);
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

int	main(int argc, char *argv[])
{
	t_mlx 			min;
	t_map_info 		map;
	t_view_cord 	*pvcord;

	if (argc != 2)
	{
		perror("program filename");
		return (-1);
	}
	min.mlx_ptr = mlx_init();
	if (min.mlx_ptr == 0)
	{
		perror("can't open connection Xwinodw");
		return (-1);
	}
	min.win_ptr = mlx_new_window(min.mlx_ptr, 2000, 2000, "first my Winodw for minilibX");
	if (min.win_ptr == 0)
	{
		perror("can't create new window");
		return (-1);
	}

	mlx_mouse_hook(min.win_ptr, mouse_event, 0);
	mlx_expose_hook(min.win_ptr, expose_event, &min);	
	mlx_hook(min.win_ptr, 17, 0, close_event, &min);
	
	min.img_ptr = mlx_new_image(min.mlx_ptr, 2000, 2000);
	if (min.img_ptr == 0)
	{
		perror("can't create new image");
		return (-1);
	}
	t_img	img;

	img.addr = (unsigned int *)mlx_get_data_addr(min.img_ptr, &img.bpp, &img.size_line, &img.endian);
	if (img.addr == 0)
		return (-1);
	printf("bpp : %d, size_line : %d, endian : %d\n", img.bpp, img.size_line, img.endian);
	
	if (fill_map_data(argv[1], &map) < 0)
		return (-1);
	pvcord = malloc(sizeof(t_view_cord) * map.width * map.height);
	if (pvcord == NULL)
		return (-1);
	printf("map: width : %d, height: %d\n", map.width, map.height);
	
	t_draw_info draw_info;
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
	init_matrix(&m_rotate);
	init_matrix(&m_view);
	multiply_matrix(draw_info.pm_iso, draw_info.pm_rotate, draw_info.pm_view);
	fill_cordinate_view(&draw_info);
	make_view_cordinate(&draw_info);
	draw_screen(&draw_info);

	mlx_key_hook(min.win_ptr, key_event, &draw_info);
	mlx_loop(min.mlx_ptr);
	return (0);
}
