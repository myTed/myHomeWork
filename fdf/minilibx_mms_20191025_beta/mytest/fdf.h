/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/03 20:17:44 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	SCREEN_DX		30
#define	SCREEN_DY		30
#define SCREEN_DZ		10
#define	PI				3.1415926535
#define	ROTATION_DEGREE	10.0
#define ESC 		53//65307	
#define END_ROL_X	117//65367	
#define DEL_ROL_Y	119//65535
#define PGDN_ROL_Z	121//65366
#define	UP			126//65362				
#define DOWN		125//65364
#define LEFT		123//65361
#define RIGHT		124//65363
#define SCALE_UP	115//65360
#define SCALE_DOWN	116//65365

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

typedef struct s_rotate_cord
{
	double	x;
	double	y;
	double	z;
} t_rotate_cord;

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
	t_rotate_cord	*prcord;
	t_mlx			*pmlx;
	double			scale;
	double			down;
	double			right;	
} t_draw_info;

int	ft_atoi_base(char *str, char *base);
int	fill_map_data(char *file_name, t_map_info *pmap);

void rotate_rcord_x(t_draw_info *pdi, double angle);

void rotate_rcord_y(t_draw_info *pdi, double angle);

void rotate_rcord_z(t_draw_info *pid, double angle);

void rotate_x(double *px, double *py, double *pz, double angle);
void rotate_y(double *px, double *py, double *pz, double angle);
void rotate_z(double *px, double *py, double *pz, double angle);
