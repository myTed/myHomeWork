/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 15:34:17 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# define SCREEN_WIDTHS		2000
# define SCREEN_HEIGHTS		2000
# define SCREEN_DX			30
# define SCREEN_DY			30
# define SCREEN_DZ			0.8
# define PI					3.1415926535
# define ROTATION_DEGREE	10.0
# define ESC 				53//65307	
# define END_ROL_X			117//65367	
# define DEL_ROL_Y			119//65535
# define PGDN_ROL_Z			121//65366
# define UP					126//65362				
# define DOWN				125//65364
# define LEFT				123//65361
# define RIGHT				124//65363
# define SCALE_UP			115//65360
# define SCALE_DOWN			116//65365
# define FRONT_VIEW			18
# define TOP_VIEW			19
# define RIGHT_VIEW			20

typedef struct s_color
{
	unsigned int	blue:8;
	unsigned int	green:8;
	unsigned int	red:8;
	unsigned int	padd:8;
}	t_color;

typedef struct s_cordinate
{
	double	x;
	double	y;
	double	z;
}	t_cordinate;

typedef struct s_map_info
{
	int				width;
	int				height;
	t_cordinate		*pcord;
}	t_map_info;

typedef struct s_view_cord
{
	double	x;
	double	y;
	double	z;
	t_color	color;
}	t_view_cord;

typedef struct s_draw_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	width;
	int	height;
	int	del_x;
	int	del_y;
}	t_draw_point;

typedef struct s_img
{
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_mlx;

typedef double	t_row[3];

typedef struct s_matrix
{
	union {
		struct {
			t_row	r1;
			t_row	r2;
			t_row	r3;
		};
		double	m[3][3];
	};
}	t_matrix;

typedef struct m_info
{
	t_matrix	m_iso;
	t_matrix	m_view;
	t_matrix	m_rotate;
}	t_mat_info;

typedef struct s_info
{
	t_mlx			mlx;
	t_img			img;
	t_map_info		map;
	t_view_cord		*pvcord;
	t_mat_info		matrix;
	double			scale;
	double			down;
	double			right;	
}	t_draw_info;

int		draw_line(t_img *pimg, t_draw_point *pdp, t_color color);
int		project_map(t_draw_info *pdi);
int		key_event(int keycode, void *param);
int		is_valid_map_file(char *file_name, t_map_info *pmap);
int		fill_cord_from_map_file(char *file_name, t_map_info *pmap);
int		make_unit_matrix(t_matrix *prm);
int		make_matrix_isometric(t_draw_info *pdi);
int		make_view_cordinate(t_draw_info *pdi);
int		multiply_matrix(t_matrix *pvm, t_matrix *prm, t_matrix *pdest);
int		make_matrix_rotate_x(t_matrix *pm, double angle);
int		make_matrix_rotate_y(t_matrix *pm, double angle);
int		make_matrix_rotate_z(t_matrix *pm, double angle);
int		make_matrix_right(t_matrix *prvm);
int		make_matrix_front(t_matrix *pfvm);
int		make_matrix_top(t_matrix *ptvm);
#endif
