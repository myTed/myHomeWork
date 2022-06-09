/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/09 00:54:38 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	SCREEN_DX		10
#define	SCREEN_DY		10
#define SCREEN_DZ		5
#define	PI				3.1415926535
#define	ROTATION_DEGREE	10.0
#define ESC 		65307//53//65307	
#define END_ROL_X	65367//117//65367	
#define DEL_ROL_Y	65535//119//65535
#define PGDN_ROL_Z	65366//121//65366
#define	UP			65362//126//65362				
#define DOWN		65364//125//65364
#define LEFT		65361//123//65361
#define RIGHT		65363//124//65363
#define SCALE_UP	65360//115//65360
#define SCALE_DOWN	65365//116//65365
#define FRONT_VIEW	18
#define TOP_VIEW	19
#define	RIGHT_VIEW	20
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


typedef double t_row[3];

typedef struct s_matrix
{
	union {
		struct {
			double _11, _12, _13;
			double _21, _22, _23;
			double _31, _32, _33;
		};
		struct {
			t_row   r1;
			t_row   r2;
			t_row   r3;
		};
		double m[3][3];
	};
} t_matrix;

typedef struct s_info
{
	t_img			*pimg;
	t_map_info		*pmap;
	t_view_cord		*pvcord;
	t_rotate_cord	*prcord;
	t_mlx			*pmlx;
	t_matrix		*pm_iso;
	t_matrix		*pm_rotate;
	t_matrix		*pm_view;
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
void	init_matrix(t_matrix *prm);
void	make_final_matrix(t_draw_info *pdi);
void	make_matrix_isometric(t_draw_info *pdi);
void	make_view_cordinate(t_draw_info *pdi);
void	multiply_matrix(t_matrix *pvm, t_matrix *prm, t_matrix *pdest);
void	make_matrix_rotate_x(t_matrix *pm, double angle);
void	make_matrix_rotate_y(t_matrix *pm, double angle);
void	make_matrix_rotate_z(t_matrix *pm, double angle);
void	make_matrix_right_view(t_matrix *prvm);
void	make_matrix_front_view(t_matrix *pfvm);
void	make_matrix_top_view(t_matrix *ptvm);
