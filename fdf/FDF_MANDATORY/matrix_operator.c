/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:53:28 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:17:45 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include "../libft/libft.h"
#include <math.h>

int	make_matrix_minus_z(t_matrix *prm);
int	draw_screen(t_draw_info *pdi);

int	multiply_matrix(t_matrix *pvm, t_matrix *prm, t_matrix *pdest)
{
	int			idx;
	t_matrix	tmp;

	if ((pvm == 0) || (prm == 0) || (pdest == 0))
		return (-1);
	ft_memset(&tmp, 0, sizeof(t_matrix));
	idx = 0;
	while (idx < 3)
	{
		tmp.r1[idx] += pvm->r1[0] * prm->r1[idx];
		tmp.r1[idx] += pvm->r1[1] * prm->r2[idx];
		tmp.r1[idx] += pvm->r1[2] * prm->r3[idx];
		tmp.r2[idx] += pvm->r2[0] * prm->r1[idx];
		tmp.r2[idx] += pvm->r2[1] * prm->r2[idx];
		tmp.r2[idx] += pvm->r2[2] * prm->r3[idx];
		tmp.r3[idx] += pvm->r3[0] * prm->r1[idx];
		tmp.r3[idx] += pvm->r3[1] * prm->r2[idx];
		tmp.r3[idx] += pvm->r3[2] * prm->r3[idx];
		idx++;
	}
	ft_memcpy(pdest, &tmp, sizeof(tmp));
	return (0);
}

int	multiply_vector(t_matrix *pvm, t_view_cord *psrc, t_view_cord *pdest)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	if ((pvm == 0) || (psrc == 0) || (pdest == 0))
		return (-1);
	tmp_x = psrc->x;
	tmp_y = psrc->y;
	tmp_z = psrc->z;
	pdest->x = (pvm->r1[0] * tmp_x) + (pvm->r1[1] * tmp_y)
		+ (pvm->r1[2] * tmp_z);
	pdest->y = (pvm->r2[0] * tmp_x) + (pvm->r2[1] * tmp_y)
		+ (pvm->r2[2] * tmp_z);
	pdest->z = (pvm->r3[0] * tmp_x) + (pvm->r3[2] * tmp_y)
		+ (pvm->r3[2] * tmp_z);
	return (0);
}

int	make_view_cordinate(t_draw_info *pdi)
{
	int	idx;

	if (pdi == 0)
		return (-1);
	idx = 0;
	while (idx < pdi->map.width * pdi->map.height)
	{
		pdi->pvcord[idx].x = pdi->map.pcord[idx].x - (pdi->map.width / 2);
		pdi->pvcord[idx].y = pdi->map.pcord[idx].y - (pdi->map.height / 2);
		pdi->pvcord[idx].z = pdi->map.pcord[idx].z * SCREEN_DZ;
		idx++;
	}
	idx = 0;
	while (idx < (pdi->map.height) * (pdi->map.width))
	{
		multiply_vector(&pdi->matrix.m_view, &(pdi->pvcord[idx]),
			&(pdi->pvcord[idx]));
		idx++;
	}
	return (0);
}

int	make_matrix_isometric(t_draw_info *pdi)
{
	t_matrix	z;
	t_matrix	x;
	t_matrix	minus_z;
	t_matrix	tmp;

	if (pdi == 0)
		return (-1);
	make_matrix_rotate_z(&z, 45);
	make_matrix_rotate_x(&x, 35.264);
	make_matrix_minus_z(&minus_z);
	multiply_matrix(&x, &z, &tmp);
	multiply_matrix(&minus_z, &tmp, &pdi->matrix.m_iso);
	return (0);
}

int	project_map(t_draw_info *pdi)
{
	t_matrix	*pm_view;
	t_matrix	*pm_rotate;

	if (pdi == 0)
		return (-1);
	pm_view = &(pdi->matrix.m_view);
	pm_rotate = &(pdi->matrix.m_rotate);
	if (make_matrix_isometric(pdi) < 0)
		return (-1);
	if (make_unit_matrix(pm_rotate) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_iso, pm_rotate, pm_view) < 0)
		return (-1);
	if (make_view_cordinate(pdi) < 0)
		return (-1);
	if (draw_screen(pdi) < 0)
		return (-1);
	return (0);
}
