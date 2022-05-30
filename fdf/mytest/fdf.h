/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/05/30 00:47:41 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define	SCREEN_DX	30
#define	SCREEN_DY	30
#define SCREEN_DZ	6
#define	PI			3.1415926535
typedef struct s_color
{
	unsigned int	blue:8;
	unsigned int	green:8;
	unsigned int	red:8;
	unsigned int	padd:8;
} t_color;

typedef struct s_cordinate
{
	int	x;
	int	y;
	int	z;
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
	int	x;
	int	y;
	int	z;
	t_color color;
} t_view_cord;


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
} t_draw_info;

int	ft_atoi_base(char *str, char *base);
int	fill_map_data(char *file_name, t_map_info *pmap);
