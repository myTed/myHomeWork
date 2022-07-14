/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_scan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:10:27 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:10:28 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_minimum_value_idx(t_list *ptop, int n, int *pmin_idx)
{
	int		idx;
	t_list	*tmp_top;
	t_elem	min_value;

	if (ptop == 0)
		return (-1);
	tmp_top = ptop;
	min_value = tmp_top->data;
	*pmin_idx = 0;
	idx = 0;
	while (idx < n)
	{
		if (tmp_top->data < min_value)
		{
			min_value = tmp_top->data;
			*pmin_idx = idx;
		}
		tmp_top = tmp_top->next;
		idx++;
	}
	return (0);
}

int	is_already_ordered_stack_a(t_stack *ps, int n)
{
	int		idx;
	t_list	*ptmp_top;

	ptmp_top = ps->top_a;
	idx = 0;
	while (idx < n - 1)
	{
		if (ptmp_top->data > ptmp_top->next->data)
			return (0);
		idx++;
		ptmp_top = ptmp_top->next;
	}
	return (1);
}

int	is_already_ordered_stack_b(t_stack *ps, int n)
{
	int		idx;
	t_list	*ptmp_top;

	ptmp_top = ps->top_b;
	idx = 0;
	while (idx < n - 1)
	{
		if (ptmp_top->data < ptmp_top->next->data)
			return (0);
		idx++;
		ptmp_top = ptmp_top->next;
	}
	return (1);
}

int	is_only_data_more_than_two_third_pivot(
		t_stack *ps,
		t_pivot *ppv,
		int start_idx,
		int end_idx
){
	int		idx;
	t_list	*tmp_top;

	if (ps == 0)
		return (-1);
	idx = start_idx;
	tmp_top = ps->top_a;
	while (idx < end_idx)
	{
		if (tmp_top->data < ppv->two_third_pivot)
			return (0);
		idx++;
		tmp_top = tmp_top->next;
	}
	return (1);
}

int	is_only_data_less_than_one_third_pivot(
		t_stack *ps,
		t_pivot *ppv,
		int start_idx,
		int end_idx
){
	int		idx;
	t_list	*tmp_top;

	if (ps == 0)
		return (-1);
	idx = start_idx;
	tmp_top = ps->top_b;
	while (idx < end_idx)
	{
		if (tmp_top->data > ppv->one_third_pivot)
			return (0);
		idx++;
		tmp_top = tmp_top->next;
	}
	return (1);
}
