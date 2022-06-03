#include "../mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "fdf.h"
#include <math.h>
#include "libft/libft.h"

int draw_line(t_img *pimg, int start_y, int start_x, int end_y, int end_x, t_color color);


int make_matrix(t_draw_info *pdi)
{
	double	yaw_r;
	double	pitch_r;
	double	roll_r;
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;
	int		idx;
	double	rxx, rxy, rxz;
	double	ryx, ryy, ryz;
	double	rzx, rzy, rzz;

	yaw_r = pdi->rol_y_angle * PI / 180.0;
	pitch_r = pdi->rol_x_angle * PI / 180.0;
	roll_r = pdi->rol_z_angle * PI / 180.0;

	rxx = (cos(yaw_r) * cos(roll_r)) + (sin(yaw_r) * sin(pitch_r) * sin(roll_r));
	rxy = cos(pitch_r) * sin(roll_r);
	rxz = (-sin(yaw_r)* cos(roll_r)) + (cos(yaw_r) * sin(pitch_r) * sin(roll_r));

	ryx = (-cos(yaw_r) * sin(roll_r)) + (sin(yaw_r) * sin(pitch_r) * cos(roll_r));
	ryy = cos(pitch_r) * cos(roll_r);
	ryz = (sin(yaw_r)* sin(roll_r)) + (cos(yaw_r) * sin(pitch_r) * cos(roll_r));

	rzx = sin(yaw_r) * cos(pitch_r);
	rzy = -sin(pitch_r);
	rzz = cos(yaw_r) * cos(pitch_r);

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
		tmp_x = pdi->pvcord[idx].x;
		tmp_y = pdi->pvcord[idx].y;
		tmp_z = pdi->pvcord[idx].z;
		pdi->pvcord[idx].x = (tmp_x * rxx * pdi->scale) + (tmp_y * ryx * pdi->scale) +
						(tmp_z * rzx * pdi->scale) + pdi->up;
	
		pdi->pvcord[idx].y = (tmp_x * rxy * pdi->scale) + (tmp_y * ryy * pdi->scale) +
						(tmp_z * rzy * pdi->scale) + pdi->right;

		pdi->pvcord[idx].z = (tmp_x * rxz * pdi->scale) + (tmp_y * ryz * pdi->scale) +
						(tmp_z * rzz * pdi->scale);
		idx++;
	}
	return (0);
}


void rotate_x(double *px, double *py, double *pz, double angle)
{
	double		radian;
	double			tmp_y;

	radian = angle * PI / 180.0;
	tmp_y = *py;

	/*	
	*py = (int)((cos(radian) * (tmp_y)) - (sin(radian) * (*pz)));
	*pz = (int)((sin(radian) * (tmp_y)) + (cos(radian) * (*pz)));
	*/
	*py = (int)((cos(radian) * (tmp_y)) + (sin(radian) * (*pz)));
	*pz = (int)(-(sin(radian) * (tmp_y)) + (cos(radian) * (*pz)));
	*px = *px;
}

void rotate_y(double *px, double *py, double *pz, double angle)
{
	double		radian;
	double			tmp_x;

	radian =  angle * PI / 180.0;
	tmp_x = *px;
	/*
	*px = (int)((cos(radian) * (tmp_x)) + (sin(radian) * (*pz)));
	*pz = (int)((-sin(radian) * (tmp_x)) + (cos(radian) * (*pz)));
	*/
	*px = ((cos(radian) * (tmp_x)) - (sin(radian) * (*pz)));
	*pz = ((sin(radian) * (tmp_x)) + (cos(radian) * (*pz)));
	*py = *py;
}

void rotate_z(double *px, double *py, double *pz, double angle)
{
	double 	radian;
	double		tmp_x;
	
	radian = angle * PI / 180.0;
	tmp_x = *px;
	/*
	*px = (int)((cos(radian) * (tmp_x)) - (sin(radian) * (*py)));
	*py = (int)((sin(radian) * (tmp_x)) + (cos(radian) * (*py)));
	*/
	*px = ((cos(radian) * (tmp_x)) + (sin(radian) * (*py)));
	*py = (-(sin(radian) * (tmp_x)) + (cos(radian) * (*py)));
	
	*pz = *pz;
}


void move_xyz(int *py)
{
	*py -= 1;
}

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

int fill_view_cordinate(t_map_info *pmap, t_view_cord *pvcord)
{
	int	idx;
	t_cordinate *pcord;

	if ((pmap == 0) || (pvcord == 0))
		return (-1);
	pcord = pmap->pcord;
	idx = 0;
	while (idx < (pmap->width * pmap->height))
	{
		pvcord[idx].x = (pcord[idx].x - (pmap->height / 2 )) * (SCREEN_DX);
		pvcord[idx].y = (pcord[idx].y - (pmap->width / 2 )) *(SCREEN_DY);
		pvcord[idx].z = (pcord[idx].z * SCREEN_DZ);	
		idx++;
	}
	return (0);
}

int	iso_metric(t_draw_info *pdi)
{
	int	idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{
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

int iso_metric2(t_draw_info *pdi)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;
	int		idx;

	idx = 0;
	while (idx < pdi->pmap->width * pdi->pmap->height)
	{

		tmp_x = pdi->pvcord[idx].x;
		tmp_y = pdi->pvcord[idx].y;
		tmp_z = pdi->pvcord[idx].z;

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
		pdi->pvcord[idx].x += 1000;
		pdi->pvcord[idx].y += 1000;
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

int	key_event(int keycode, void *param)
{
	t_draw_info *pdi;
	int			idx;

	pdi = (t_draw_info *)param;

	if (keycode == ESC)
	{
		mlx_destroy_window(pdi->pmlx->mlx_ptr, pdi->pmlx->win_ptr);
		exit(0);
	}
	clear_screen(pdi);
	fill_view_cordinate(pdi->pmap, pdi->pvcord);

	if (keycode == END_ROL_X)
	{	
		pdi->rol_x_angle = (int)(pdi->rol_x_angle + 10) % 360;
		if (pdi->rol_x_angle < 0)
			pdi->rol_x_angle += 360;
		printf("angle : %lf\n", pdi->rol_x_angle);			
		make_matrix(pdi);
		/*
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			rotate_x(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_x_angle);
			rotate_y(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_y_angle);
			rotate_z(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_z_angle);
			idx++;
		}
		*/
		iso_metric(pdi);
	}
	else if (keycode == DEL_ROL_Y)
	{
		pdi->rol_y_angle = (int)(pdi->rol_y_angle + 10) % 360;
		if (pdi->rol_y_angle < 0)
			pdi->rol_y_angle += 360;
		printf("angle : %lf\n", pdi->rol_y_angle);
		make_matrix(pdi);
		/*		
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			rotate_x(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_x_angle);
			rotate_y(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_y_angle);
			rotate_z(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_z_angle);
			idx++;
		}
		*/
		iso_metric(pdi);
	}
	else if (keycode == PGDN_ROL_Z)
	{
		pdi->rol_z_angle = (int)(pdi->rol_z_angle + 10) % 360;
		if (pdi->rol_z_angle < 0)
			pdi->rol_z_angle += 360;
		printf("angle : %lf\n", pdi->rol_z_angle);			
		make_matrix(pdi);
		/*
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			rotate_x(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_x_angle);
			rotate_y(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_y_angle);
			rotate_z(&(pdi->pvcord[idx].x), &(pdi->pvcord[idx].y), &(pdi->pvcord[idx].z), 360 - pdi->rol_z_angle);
			idx++;
		}
		*/
		iso_metric(pdi);
	}
	else if (keycode == UP)
	{
		pdi->right -= SCREEN_DX;
		//pdi->right = 0;
		make_matrix(pdi);
		
		
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x -= pdi->right;
			idx++;
		}
		
		iso_metric(pdi);
		
	}
	else if (keycode == DOWN)
	{
		pdi->right += SCREEN_DY;
		//pdi->right = 0;
		make_matrix(pdi);	
		
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x -= pdi->right;
			idx++;
		}
		
		iso_metric(pdi);
		
		/*
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].y += pdi->up;
			idx++;
		}
		*/
	}
	else if (keycode == LEFT)
	{
		pdi->right -= SCREEN_DX;
		make_matrix(pdi);
		iso_metric(pdi);
		/*
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += 1000;
			pdi->pvcord[idx].y += 1000;
			idx++;
		}
		*/
		
		/*
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += pdi->right;
			idx++;
		}
		*/
		
	}
	else if (keycode == RIGHT)
	{
		pdi->right += SCREEN_DX;
		make_matrix(pdi);
		iso_metric(pdi);
		/*
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += 1000;
			pdi->pvcord[idx].y += 1000;
			idx++;
		}
		*/
		/*	
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += pdi->right;
			idx++;
		}
		*/
	}
	else if (keycode == SCALE_UP)
	{
		pdi->scale += 0.2;
		if (pdi->scale == 4.0)
			pdi->scale = 4.0;
		make_matrix(pdi);
		iso_metric(pdi);
		/*
		pdi->up += 40;
		if (pdi->up > 400)
			pdi->up = 400;
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x *= 1 + (pdi->up /100.0);
			pdi->pvcord[idx].y *= 1 + (pdi->up /100.0);
			pdi->pvcord[idx].z *= 1 + (pdi->up /100.0);
			idx++;
		}
		//iso_metric(pdi);
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += 1000;
			pdi->pvcord[idx].y += 1000;
			idx++;
		}
		*/
		printf("scale up\n");
	}
	else if (keycode == SCALE_DOWN)
	{
		pdi->scale -= 0.2;
		if (pdi->scale < 0.1)
			pdi->scale = 0.1;
		make_matrix(pdi);
		iso_metric(pdi);
		/*
		pdi->up -= 40;
		if (pdi->up < 0)
			pdi->up = 0;
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x *= 1 + (pdi->up /100.0);
			pdi->pvcord[idx].y *= 1 + (pdi->up /100.0);
			pdi->pvcord[idx].z *= 1 + (pdi->up /100.0);
			idx++;
		}
		idx = 0;
		while (idx < pdi->pmap->width * pdi->pmap->height)
		{
			pdi->pvcord[idx].x += 1000;
			pdi->pvcord[idx].y += 1000;
			idx++;
		}
		*/
		printf("scale down\n");
	}
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
	if (start_x < 0 || start_x > 2000)
		return (-1);
	if (start_y < 0 || start_y > 2000)
		return (-1);
	if (end_x < 0 || end_x > 2000)
		return (-1);
	if (end_y < 0 || end_y > 2000)
		return (-1);
	//set_pixel(pimg, start_y, start_x, col);
	
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
	//t_color	col;
	t_img	img;

	img.addr = (unsigned int *)mlx_get_data_addr(min.img_ptr, &img.bpp, &img.size_line, &img.endian);
	if (img.addr == 0)
		return (-1);
	printf("bpp : %d, size_line : %d, endian : %d\n", img.bpp, img.size_line, img.endian);
	
	if (fill_map_data(argv[1], &map) < 0)
		return (-1);
	pvcord = malloc(sizeof(t_view_cord) * map.width * map.height);
	if (pvcord == 0)
		return (-1);
	if (fill_view_cordinate(&map, pvcord) < 0)
		return (-1);
	
	printf("map: width : %d, height: %d\n", map.width, map.height);
	
	t_draw_info draw_info;
	ft_memset(&draw_info, 0, sizeof(t_draw_info));

	draw_info.pimg = &img;
	draw_info.pmap = &map;
	draw_info.pvcord = pvcord;
	draw_info.pmlx = &min;
	draw_info.scale = 1.0;
		
	make_matrix(&draw_info);
	iso_metric(&draw_info);
	
	draw_screen(&draw_info);

	mlx_key_hook(min.win_ptr, key_event, &draw_info);
	mlx_loop(min.mlx_ptr);
	return (0);
}




