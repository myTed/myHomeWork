/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/03 06:12:55 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	SCREEN_DX	30
#define	SCREEN_DY	30
#define SCREEN_DZ	10
#define	PI			3.1415926535

#define ESC 		65307	
#define END_ROL_X	65367	
#define DEL_ROL_Y	65535
#define PGDN_ROL_Z	65366
#define	UP			65362				
#define DOWN		65364
#define LEFT		65361
#define RIGHT		65363
#define SCALE_UP	65360
#define SCALE_DOWN	65365

typedef struct s_color
{
	unsigned int	blue:8;
	unsigned int	green:8;
	unsigned int	red:8;
	unsigned int	padd:8;
} t_color;

typedef struct s_cordinate
{
	double	x;
	double	y;
	double	z;
	t_color color;
} t_cordinate;

typedef struct s_map_info
{
	int			width;
	int			height;
	t_cordinate *pcord;
} t_map_info;


typedef struct s_view_cord
{
	double	x;
	double	y;
	double	z;
	t_color color;
} t_view_cord;

typedef struct s_camera
{
	int	x;
	int	y;
	int	z;
} t_camera_view;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
} t_mlx;

typedef struct s_img
{
	unsigned int    *addr;
	int             bpp;
	int             size_line;
	int             endian;
} t_img;


typedef struct s_info
{
	t_img			*pimg;
	t_map_info		*pmap;
	t_view_cord		*pvcord;
	t_mlx			*pmlx;
	double			scale;
	double			rol_x_angle;
	double			rol_y_angle;
	double			rol_z_angle;
	double			up;
	double			right;	
} t_draw_info;

int	ft_atoi_base(char *str, char *base);
int	fill_map_data(char *file_name, t_map_info *pmap);

