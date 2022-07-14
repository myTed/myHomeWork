/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_under_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:10:54 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:12:24 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_maximum_value_idx(t_list *ptop, int n, int *pmax_idx)
{
	int		idx;
	t_list	*tmp_top;
	t_elem	max_value;

	if (ptop == 0)
		return (-1);
	tmp_top = ptop;
	max_value = tmp_top->data;
	*pmax_idx = 0;
	idx = 0;
	while (idx < n)
	{
		if (tmp_top->data > max_value)
		{
			max_value = tmp_top->data;
			*pmax_idx = idx;
		}
		tmp_top = tmp_top->next;
		idx++;
	}
	return (0);
}

int	quick_sort_a_size_3(t_stack *ps, int n)
{
	int	max_idx;

	if (ps == 0)
		return (-1);
	if (find_maximum_value_idx(ps->top_a, n, &max_idx) < 0)
		return (-1);
	if (max_idx == 2)
	{
		if (ps->top_a->data > ps->top_a->next->data)
			sa(ps);
		return (0);
	}
	if (ps->top_a->data > ps->top_a->next->data)
		sa(ps);
	pb(ps);
	if (ps->top_a->data > ps->top_a->next->data)
		sa(ps);
	pa(ps);
	if (ps->top_a->data > ps->top_a->next->data)
		sa(ps);
	return (0);
}

int	quick_sort_b_size_3(t_stack *ps, int n)
{
	int	max_idx;

	if (ps == 0)
		return (-1);
	if (find_maximum_value_idx(ps->top_b, n, &max_idx) < 0)
		return (-1);
	if (max_idx == 0)
	{
		pa(ps);
		if (ps->top_b->data < ps->top_b->next->data)
			sb(ps);
		pa(ps);
		pa(ps);
		return (0);
	}
	if (ps->top_b->data < ps->top_b->next->data)
		sb(ps);
	pa(ps);
	if (ps->top_b->data < ps->top_b->next->data)
		sb(ps);
	pa(ps);
	if (ps->top_a->data > ps->top_a->next->data)
		sa(ps);
	pa(ps);
	return (0);
}

int	sort_size_3_under_b(t_stack *ps, int n)
{
	if (ps == 0)
		return (-1);
	if (n == 2)
	{
		if (ps->top_b->data < ps->top_b->next->data)
			sb(ps);
		pa(ps);
		pa(ps);
		return (0);
	}
	if (quick_sort_b_size_3(ps, n) < 0)
		return (-1);
	return (0);
}

int	sort_size_3_under_a(t_stack *ps, int n)
{
	if (ps == 0)
		return (-1);
	if (n == 2)
	{
		if (ps->top_a->data > ps->top_a->next->data)
			sa(ps);
		return (0);
	}
	if (quick_sort_a_size_3(ps, n) < 0)
		return (-1);
	return (0);
}
