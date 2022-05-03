#include "../mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC 53

typedef struct s_color
{
	unsigned int	blue :8;
	unsigned int	green :8;
	unsigned int	red	  :8;
	unsigned int	zero  :8;
} t_color;


int	key_event(int keycode)
{
	if (keycode == ESC)
		exit(1);
	printf("%d\n", keycode);
	return (0);
}


int	mouse_event(int button, int x, int y)
{
	printf("button: %d (%d, %d)\n", button, x, y);
	return (0);
}


int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;

	int		i;
	t_color	px_color;

	mlx_ptr = mlx_init();
	if (mlx_ptr == 0)
	{
		perror("can't connect to x window server");
		exit(1);
	}
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "test1");
	if (win_ptr == 0)
	{
		perror("can't make window");
		exit(1);
	}
	
	mlx_key_hook(win_ptr, key_event, 0);
	mlx_mouse_hook(win_ptr, mouse_event, 0);

	i = 0;
	px_color.zero = 0;
	px_color.red = 255;
	px_color.green = 255;
	px_color.blue = 0;
	int	*pcolor;

	
	pcolor = (int *)&px_color;
	/*
	while (i < 100)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, 100, 100 + i, *pcolor);
		i++;
	}
	i+=10;
	*/
	//mlx_string_put(mlx_ptr, win_ptr, 100, 100, *pcolor, "I'm test!!!!");	
	img_ptr = mlx_new_image(mlx_ptr, 200, 200);
	if (img_ptr == 0)
	{
		perror("can't make new image");
		return (-1);
	}
	int	bpp;
	int	size_line;
	int	endian;
	char	*image_addr;

	image_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	if (image_addr == 0)
	{
		perror("can't get data addr");
		return (-1);
	}
	printf("bpp : %d, size_line : %d, endian : %d, image_addr : %p\n", 
			bpp, size_line, endian, image_addr);
	
	t_color green;
	green.zero = 0;
	green.red = 0;
	green.green = 255;
	green.blue = 0;
	unsigned int	tr_fm_color;

	tr_fm_color = mlx_get_color_value(mlx_ptr, *(int *)&green);
	int *piaddr;
	printf("tr_fm_color : %d\n", tr_fm_color);
	piaddr = (int *)image_addr;
	i = 0;
	
	while (i < 100)
	{
		piaddr[i] = *(int *)&tr_fm_color;
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

	mlx_loop(mlx_ptr);
	return (0);
}
