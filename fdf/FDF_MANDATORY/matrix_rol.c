/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:24:16 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:18:11 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include "../libft/libft.h"
#include <math.h>

int	make_matrix_rotate_x(t_matrix *pm, double angle)
{
	double	rad;

	if (pm == 0)
		return (-1);
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
	return (0);
}

int	make_matrix_rotate_y(t_matrix *pm, double angle)
{
	double	rad;

	if (pm == 0)
		return (-1);
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
	return (0);
}

int	make_matrix_rotate_z(t_matrix *pm, double angle)
{
	double	rad;

	if (pm == 0)
		return (-1);
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
	return (0);
}

int	make_unit_matrix(t_matrix *prm)
{
	if (prm == 0)
		return (-1);
	ft_memset(prm, 0, sizeof(t_matrix));
	prm->m[0][0] = 1;
	prm->m[1][1] = 1;
	prm->m[2][2] = 1;
	return (0);
}

int	make_matrix_minus_z(t_matrix *prm)
{
	if (prm == 0)
		return (-1);
	ft_memset(prm, 0, sizeof(t_matrix));
	prm->m[0][0] = 1;
	prm->m[1][1] = 1;
	prm->m[2][2] = -1;
	return (0);
}
