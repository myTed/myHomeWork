/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rol_view_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:24:24 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 15:38:51 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"

int	make_matrix_rol_x_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;

	if (pdi == 0)
		return (-1);
	if (make_matrix_rotate_x(&m_rotate, 10) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_rotate,
			&m_rotate, &pdi->matrix.m_rotate) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_iso, &pdi->matrix.m_rotate,
			&pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}

int	make_matrix_rol_y_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;

	if (pdi == 0)
		return (-1);
	if (make_matrix_rotate_y(&m_rotate, 10) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_rotate, &m_rotate,
			&pdi->matrix.m_rotate) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_iso, &pdi->matrix.m_rotate,
			&pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}

int	make_matrix_rol_z_view(t_draw_info *pdi)
{
	t_matrix	m_rotate;

	if (pdi == 0)
		return (-1);
	if (make_matrix_rotate_z(&m_rotate, 10) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_rotate, &m_rotate,
			&pdi->matrix.m_rotate) < 0)
		return (-1);
	if (multiply_matrix(&pdi->matrix.m_iso, &pdi->matrix.m_rotate,
			&pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}
