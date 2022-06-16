/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_parallel_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:23:03 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 03:18:03 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"

int	make_matrix_top_view(t_draw_info *pdi)
{
	t_matrix	m_top;
	t_matrix	m_unit;

	if (pdi == 0)
		return (-1);
	if (make_matrix_top(&m_top) < 0)
		return (-1);
	if (make_unit_matrix(&m_unit) < 0)
		return (-1);
	if (multiply_matrix(&m_top, &m_unit, &pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}

int	make_matrix_right_view(t_draw_info *pdi)
{
	t_matrix	m_right;
	t_matrix	m_unit;

	if (pdi == 0)
		return (-1);
	if (make_matrix_right(&m_right) < 0)
		return (-1);
	if (make_unit_matrix(&m_unit) < 0)
		return (-1);
	if (multiply_matrix(&m_right, &m_unit, &pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}

int	make_matrix_front_view(t_draw_info *pdi)
{
	t_matrix	m_front;
	t_matrix	m_unit;

	if (pdi == 0)
		return (-1);
	if (make_matrix_front(&m_front) < 0)
		return (-1);
	if (make_unit_matrix(&m_unit) < 0)
		return (-1);
	if (multiply_matrix(&m_front, &m_unit, &pdi->matrix.m_view) < 0)
		return (-1);
	return (0);
}
