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

void multiply_vector(t_matrix *pvm, t_cordinate *porg, t_view_cord *pview)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = porg->x;
	tmp_y = porg->y;
	tmp_z = porg->z;
	pview->x = (pvm->r1[0] * tmp_x) + (pvm->r1[1] * tmp_y) + (pvm->r1[2] * tmp_z);
	pview->y = (pvm->r2[0] * tmp_x) + (pvm->r2[1] * tmp_y) + (pvm->r2[2] * tmp_z);
	pview->z = (pvm->r3[0] * tmp_x) + (pvm->r3[2] * tmp_y) + (pvm->r3[2] * tmp_z);
}

void make_view_cordinate(t_draw_info *pdi)
{
	int idx;

	idx = 0;
	while (idx < (pdi->pmap->height) * (pdi->pmap->width))
	{
		multiply_vector(pdi->pview_m, &(pdi->pmap->pcord[idx]), &(pdi->pvcord[idx]));
		idx++;
	}
}

void make_matrix_isometric(t_draw_info *pdi)
{
	t_matrix	z;
	t_matrix	x;
	//t_matrix	y;
	t_matrix	tmp;

	
	make_matrix_rotate_z(&z, -180);
	make_matrix_rotate_x(&x, -(90 + 35.264));
	multiply_matrix(&z, &x, &tmp);
	make_matrix_rotate_z(&z, 45);
	multiply_matrix(&tmp, &z, pdi->piso_m);
}

void	init_matrix(t_matrix *prm)
{
	ft_memset(prm, 0, sizeof(t_matrix));
	prm->m[0][0] = 1;
	prm->m[1][1] = 1;
	prm->m[2][2] = 1;
}

void make_final_matrix(t_draw_info *pdi)
{
	multiply_matrix(pdi->piso_m, pdi->protate_m, pdi->pview_m);
}


