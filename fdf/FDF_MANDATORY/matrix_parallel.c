/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 02:24:09 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/15 15:46:49 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_fdf.h"
#include "../libft/libft.h"

int	make_matrix_top(t_matrix *ptvm)
{
	if (ptvm == 0)
		return (-1);
	ft_memset(ptvm, 0, sizeof(t_matrix));
	ptvm->m[0][0] = 1;
	ptvm->m[1][1] = 1;
	ptvm->m[2][2] = -1;
	return (0);
}

int	make_matrix_front(t_matrix *pfvm)
{
	if (pfvm == 0)
		return (-1);
	ft_memset(pfvm, 0, sizeof(t_matrix));
	pfvm->m[0][0] = 1;
	pfvm->m[1][2] = -1;
	pfvm->m[2][1] = -1;
	return (0);
}

int	make_matrix_right(t_matrix *prvm)
{
	if (prvm == 0)
		return (-1);
	ft_memset(prvm, 0, sizeof(t_matrix));
	prvm->m[0][1] = -1;
	prvm->m[1][2] = -1;
	prvm->m[2][0] = -1;
	return (0);
}
