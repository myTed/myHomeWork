/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_transfer_a_to_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:09:26 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:10:20 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	transfer_final_data_smaller_two_third_pivot(
		t_stack *ps,
		t_partition_info *ppi
){
	if ((ps == 0) || (ppi == 0))
		return (-1);
	if ((ps->top_a->next->data < ppi->pv.two_third_pivot))
	{
		sa(ps);
		ppi->skip_ra_cnt++;
		pb(ps);
		ppi->pb_cnt++;
		if (ps->top_b->data >= ppi->pv.one_third_pivot)
		{
			rb(ps);
			ppi->rb_cnt++;
		}
		return (1);
	}
	return (0);
}

int	first_transfer_smaller_pivot(
		t_stack *ps,
		t_partition_info *ppi
){
	if ((ps == 0) || (ppi == 0))
		return (-1);
	if (ps->top_a->data >= ppi->pv.two_third_pivot)
	{
		ra(ps);
		ppi->ra_cnt++;
	}
	else
	{
		pb(ps);
		ppi->pb_cnt++;
		if (ps->top_b->data < ppi->pv.one_third_pivot)
			rb(ps);
		else
			ppi->rb_cnt++;
	}
	return (0);
}

int	first_transfer_smaller_data_than_two_third_pivot(
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	int	idx;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	while (idx < n)
	{
		if (is_only_data_more_than_two_third_pivot(ps, &(ppi->pv), idx, n) == 1)
		{
			ppi->skip_ra_cnt = n - idx;
			return (0);
		}
		else
		{
			if (first_transfer_smaller_pivot(ps, ppi) < 0)
				return (-1);
		}
		idx++;
	}
	return (0);
}

int	transfer_smaller_pivot(
		t_stack *ps,
		int idx,
		int n,
		t_partition_info *ppi
){
	if ((ps == 0) || (ppi == 0))
		return (-1);
	if (ps->top_a->data >= ppi->pv.two_third_pivot)
	{
		if (idx == n - 2)
		{
			if (transfer_final_data_smaller_two_third_pivot(ps, ppi) == 1)
				return (0);
		}
		ra(ps);
		ppi->ra_cnt++;
	}
	else
	{
		pb(ps);
		ppi->pb_cnt++;
		if (ps->top_b->data >= ppi->pv.one_third_pivot)
		{
			rb(ps);
			ppi->rb_cnt++;
		}
	}
	return (0);
}

int	transfer_smaller_data_than_two_third_pivot(
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	int		idx;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	while (idx < n)
	{
		if (is_only_data_more_than_two_third_pivot(ps, &(ppi->pv), idx, n) == 1)
		{
			ppi->skip_ra_cnt = n - idx;
			return (0);
		}
		else
		{
			if (transfer_smaller_pivot(ps, idx, n, ppi) < 0)
				return (-1);
		}	
		idx++;
	}
	return (0);
}
