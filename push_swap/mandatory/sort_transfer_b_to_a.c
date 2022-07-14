/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_transfer_b_to_a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:13:51 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:13:58 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	transfer_bigger_data_than_pivot(t_stack *ps, int n, int pivot)
{
	int		idx;
	int		pa_cnt;
	t_elem	data;

	idx = 0;
	pa_cnt = 0;
	while (idx < n)
	{
		data = ps->top_b->data;
		if (data >= pivot)
		{
			pa(ps);
			pa_cnt++;
		}
		else
			rb(ps);
		idx++;
	}
	return (n - pa_cnt);
}

int	transfer_final_data_bigger_one_third_pivot(
		t_stack *ps,
		t_partition_info *ppi
){
	if ((ps == 0) || (ppi == 0))
		return (-1);
	if ((ps->top_b->next->data >= ppi->pv.one_third_pivot))
	{
		sb(ps);
		ppi->skip_rb_cnt++;
		pa(ps);
		ppi->pa_cnt++;
		if (ps->top_a->data < ppi->pv.two_third_pivot)
		{
			ra(ps);
			ppi->ra_cnt++;
		}
		return (1);
	}
	return (0);
}

int	transfer_bigger_data_pivot(
		t_stack *ps,
		int idx,
		int n,
		t_partition_info *ppi
){
	if ((ps == 0) || (ppi == 0))
		return (-1);
	if (ps->top_b->data < ppi->pv.one_third_pivot)
	{
		if (idx == n - 2)
		{
			if (transfer_final_data_bigger_one_third_pivot(ps, ppi) == 1)
				return (0);
		}
		rb(ps);
		ppi->rb_cnt++;
	}
	else
	{
		pa(ps);
		ppi->pa_cnt++;
		if (ps->top_a->data < ppi->pv.two_third_pivot)
		{
			ra(ps);
			ppi->ra_cnt++;
		}
	}
	return (0);
}

int	transfer_bigger_data_than_one_third_pivot(
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
		if (is_only_data_less_than_one_third_pivot(ps, &(ppi->pv), idx, n) == 1)
		{
			ppi->skip_rb_cnt = n - idx;
			return (0);
		}
		else
		{
			if (transfer_bigger_data_pivot(ps, idx, n, ppi) < 0)
				return (-1);
		}	
		idx++;
	}
	return (0);
}
