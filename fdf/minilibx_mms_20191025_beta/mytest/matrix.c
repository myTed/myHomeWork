#include "fdf.h"
#include "libft/libft.h"
#include <math.h>

void	make_matrix_rotate_x(t_matrix *pm, double angle)
{
	double rad;

	rad = PI * angle / 180.0;
	pm->r1[0] = 1;
	pm->r1[1] = 0;
	pm->r1[2] = 0;
	pm->r2[0] = 0;
	pm->r2[1] = cos(rad);
	pm->r2[2] = -sin(rad);
	pm->r3[0] = 0;
	pm->r3[1] = sin(rad);
	pm->r3[2] = cos(rad);
}

void	make_matrix_rotate_y(t_matrix *pm, double angle)
{
	double rad;

	rad = PI * angle / 180.0;
	
	pm->r1[0] = cos(rad);
	pm->r1[1] = 0;
	pm->r1[2] = sin(rad);
	pm->r2[0] = 0;
	pm->r2[1] = 1;
	pm->r2[2] = 0;
	pm->r3[0] = -sin(rad);
	pm->r3[1] = 0;
	pm->r3[2] = cos(rad);
}

void	make_matrix_rotate_z(t_matrix *pm, double angle)
{
	double rad;

	rad = PI * angle / 180.0;
	pm->r1[0] = cos(rad);
	pm->r1[1] = -sin(rad);
	pm->r1[2] = 0;
	pm->r2[0] = sin(rad);
	pm->r2[1] = cos(rad);
	pm->r2[2] = 0;
	pm->r3[0] = 0;
	pm->r3[1] = 0;
	pm->r3[2] = 1;
}

void	make_unit_matrix(t_matrix *prm)
{
	ft_memset(prm, 0, sizeof(t_matrix));
	prm->m[0][0] = 1;
	prm->m[1][1] = 1;
	prm->m[2][2] = 1;
}

void	make_matrix_minus_z(t_matrix *prm)
{
	ft_memset(prm, 0, sizeof(t_matrix));
	prm->m[0][0] = 1;
	prm->m[1][1] = 1;
	prm->m[2][2] = -1;

}

void	make_matrix_top_view(t_matrix *ptvm)
{
	ft_memset(ptvm, 0, sizeof(t_matrix));
	ptvm->m[0][1] = 1;
	ptvm->m[1][0] = 1;
	ptvm->m[2][2] = -1;
}

void	make_matrix_front_view(t_matrix *pfvm)
{
	ft_memset(pfvm, 0, sizeof(t_matrix));
	pfvm->m[0][1] = 1;
	pfvm->m[1][2] = -1;
	pfvm->m[2][0] = -1;
}

void	make_matrix_right_view(t_matrix *prvm)
{
	ft_memset(prvm, 0, sizeof(t_matrix));
	prvm->m[0][0] = -1;
	prvm->m[1][2] = -1;
	prvm->m[2][1] = -1;
}


void multiply_matrix(t_matrix *pvm, t_matrix *prm, t_matrix *pdest)
{
	int i;
	t_matrix	tmp;

	ft_memset(&tmp, 0, sizeof(t_matrix));
	i = 0;
	while (i < 3)
	{
		tmp.r1[i] += pvm->r1[0] * prm->r1[i];
		tmp.r1[i] += pvm->r1[1] * prm->r2[i];
		tmp.r1[i] += pvm->r1[2] * prm->r3[i];
		tmp.r2[i] += pvm->r2[0] * prm->r1[i];
		tmp.r2[i] += pvm->r2[1] * prm->r2[i];
		tmp.r2[i] += pvm->r2[2] * prm->r3[i];
		tmp.r3[i] += pvm->r3[0] * prm->r1[i];
		tmp.r3[i] += pvm->r3[1] * prm->r2[i];
		tmp.r3[i] += pvm->r3[2] * prm->r3[i];
		i++;
	}
	ft_memcpy(pdest, &tmp, sizeof(tmp));
}

void multiply_vector(t_matrix *pvm, t_view_cord *psrc, t_view_cord *pdest)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = psrc->x;
	tmp_y = psrc->y;
	tmp_z = psrc->z;
	pdest->x = (pvm->r1[0] * tmp_x) + (pvm->r1[1] * tmp_y) + (pvm->r1[2] * tmp_z);
	pdest->y = (pvm->r2[0] * tmp_x) + (pvm->r2[1] * tmp_y) + (pvm->r2[2] * tmp_z);
	pdest->z = (pvm->r3[0] * tmp_x) + (pvm->r3[2] * tmp_y) + (pvm->r3[2] * tmp_z);
}

void make_view_cordinate(t_draw_info *pdi)
{
	int idx;

	idx = 0;
	while (idx < (pdi->pmap->height) * (pdi->pmap->width))
	{
		multiply_vector(pdi->pm_view, &(pdi->pvcord[idx]), &(pdi->pvcord[idx]));
		idx++;
	}
}

void make_matrix_isometric(t_draw_info *pdi)
{
	t_matrix	z;
	t_matrix	x;
	t_matrix	minus_z;
	t_matrix	tmp;

	make_matrix_rotate_z(&z, 45);
	make_matrix_rotate_x(&x, 35.264);
	make_matrix_minus_z(&minus_z);
	multiply_matrix(&x, &z, &tmp);
	multiply_matrix(&minus_z, &tmp, pdi->pm_iso);
}
