/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:07:57 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:08:44 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/libft.h"

int	first_divide_partition_stack_a(
		t_select_stack *pss,
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	if ((pss == 0) || (ps == 0) || (ppi == 0))
		return (-1);
	ft_memset(ppi, 0, sizeof(t_partition_info));
	if (select_pivot(pss, ps->top_a, n, &(ppi->pv)) < 0)
		return (-1);
	if (first_transfer_smaller_data_than_two_third_pivot(ps, n, ppi) < 0)
		return (-1);
	return (0);
}

int	divide_partition_stack_a(
		t_select_stack *pss,
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	if ((pss == 0) || (ps == 0) || (ppi == 0))
		return (-1);
	ft_memset(ppi, 0, sizeof(t_partition_info));
	if (select_pivot(pss, ps->top_a, n, &(ppi->pv)) < 0)
		return (-1);
	if (transfer_smaller_data_than_two_third_pivot(ps, n, ppi) < 0)
		return (-1);
	return (0);
}

int	divide_partition_a(
	t_select_stack *pss,
	t_stack *ps,
	int n,
	t_partition_info *ppi
){
	if (ppi->first_partition)
	{
		if (first_divide_partition_stack_a(pss, ps, n, ppi) < 0)
			return (-1);
		ppi->first_partition = 0;
		return (0);
	}
	if (divide_partition_stack_a(pss, ps, n, ppi) < 0)
		return (-1);
	if (roll_back_stack(ps, ppi) < 0)
		return (-1);
	return (0);
}

int	divide_partition_stack_b(
		t_select_stack *pss,
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	if ((pss == 0) || (ps == 0) || (ppi == 0))
		return (-1);
	ft_memset(ppi, 0, sizeof(t_partition_info));
	if (select_pivot(pss, ps->top_b, n, &(ppi->pv)) < 0)
		return (-1);
	if (transfer_bigger_data_than_one_third_pivot(ps, n, ppi) < 0)
		return (-1);
	return (0);
}
