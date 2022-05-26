#include "../mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ESC 65307

typedef struct s_color{
	unsigned int blue:8;
	unsigned int green:8;
	unsigned int red:8;
	unsigned int zero:8;
} t_color;


typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
} t_mlx;

typedef struct s_img
{
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
} t_img;


int	key_event(int keycode, void *param)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->win_ptr);
		exit(0);
	}
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


int draw_line(t_mlx *pmlx, t_img *pimg, int start_y, int start_x, int end_y, int end_x);

int	main(int argc, char *argv[])
{
	t_mlx min;

	min.mlx_ptr = mlx_init();
	if (min.mlx_ptr == 0)
	{
		perror("can't open connection Xwinodw");
		return (-1);
	}
	min.win_ptr = mlx_new_window(min.mlx_ptr, 600, 600, "first my Winodw for minilibX");
	if (min.win_ptr == 0)
	{
		perror("can't create new window");
		return (-1);
	}

	mlx_key_hook(min.win_ptr, key_event, &min);
	mlx_mouse_hook(min.win_ptr, mouse_event, 0);
	mlx_expose_hook(min.win_ptr, expose_event, &min);	
	mlx_hook(min.win_ptr, 17, 0, close_event, &min);
	
	
	min.img_ptr = mlx_new_image(min.mlx_ptr, 600, 600);
	if (min.img_ptr == 0)
	{
		perror("can't create new image");
		return (-1);
	}


	t_color	col;
	t_img	img;


	img.addr = (unsigned int *)mlx_get_data_addr(min.img_ptr, &img.bpp, &img.size_line, &img.endian);
	if (img.addr == 0)
		return (-1);
	printf("bpp : %d, size_line : %d, endian : %d\n", img.bpp, img.size_line, img.endian);
	col.blue = 0;
	col.green = 0;
	col.red = 255;
	col.zero = 0;
	int x = 0;
	int	y = 0;

	
	while (y < 400)
	{
		x = 0;
		while (x < 400)
		{
			set_pixel(&img, y, x, col);
			x++;
		}
		y++;
	}
	
	draw_line(&min, &img, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
	//mlx_put_image_to_window(min.mlx_ptr, min.win_ptr, min.img_ptr, 0, 0);	
	mlx_loop(min.mlx_ptr);
	return (0);
}


int draw_line(t_mlx *pmlx, t_img *pimg, int start_x, int start_y, int end_x, int end_y)
{
	int	tmp_x;
	int	tmp_y;
	int	middle_eval;
	int	width;
	int	height;
	int	del_x;
	int	del_y;

	t_color	col;

	if (pimg == 0)
		return (-1);
	col.zero = 0;
	col.red = 0;
	col.green = 0;
	col.blue = 255;

	set_pixel(pimg, start_y, start_x, col);
	
	width = abs(end_x - start_x);
	height = abs(end_y - start_y);
	del_x = end_x - start_x > 0? 1 : -1;
	del_y = end_y - start_y > 0? 1: -1;
	tmp_x = start_x + del_x;
	tmp_y = start_y;
	if (height > width)
	{
		middle_eval = height - (2 * width);
		while (tmp_y != end_y)
		{
			if (middle_eval > 0)
			{
				set_pixel(pimg, tmp_y, tmp_x, col);
				middle_eval += -2 * (width);
			}
			else
			{
				tmp_x += del_x;
				set_pixel(pimg, tmp_y, tmp_x, col);
				middle_eval += 2 * (height - width);
			}
			tmp_y += del_y;
			mlx_put_image_to_window(pmlx->mlx_ptr, pmlx->win_ptr, pmlx->img_ptr, 0, 0);	
		}
	}
	else
	{
		middle_eval = (2 * height) - width;
		while (tmp_x != end_x)
		{
			if (middle_eval < 0)
			{
				set_pixel(pimg, tmp_y, tmp_x, col);
				middle_eval += 2 * (height);
			}
			else
			{
				tmp_y += del_y;
				set_pixel(pimg, tmp_y, tmp_x, col);
				middle_eval += 2 * (height - width);
			}
			tmp_x += del_x;
			mlx_put_image_to_window(pmlx->mlx_ptr, pmlx->win_ptr, pmlx->img_ptr, 0, 0);	
		}
	}
	set_pixel(pimg, end_y, end_x, col);

	return (0);
}
