/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:56:02 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/01 17:33:06 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdio.h>


int	sort_smaller(t_stack *ps, int n);
int	sort_bigger(t_stack *ps, int n);

int	select_pivot_a(t_stack *s, int n)
{
	(void)(n);
	return (s->top_a->data);
}

int	select_pivot_b(t_stack *s, int n)
{
	(void)(n);
	return (s->top_b->data);
}

int	transfer_smaller_data_than_pivot(t_stack *ps, int n, int pivot)
{
	int		idx;
	int		pb_cnt;
	t_elem	data;

	idx = 0;
	pb_cnt = 0;
	while (idx < n)
	{
		data = ps->top_a->data;
		if (data < pivot)
		{
			pb(ps);
			pb_cnt++;
		}
		else
			ra(ps);
		idx++;
	}
	return (n - pb_cnt);
}

int	sort_bigger(t_stack *ps, int n)
{
	int	pivot;
	int	remain_cnt;
	int	idx;

	if (ps == 0)
		return (-1);
	if (n <= 1)
		return (0);
	else if (n == 2)
	{
		if (ps->top_a->data > ps->top_a->next->data)
			sa(ps);
		return (0);
	}
	else
	{
		pivot = select_pivot_a(ps, n);
		remain_cnt = transfer_smaller_data_than_pivot(ps, n, pivot);
		idx = 0;
		while (idx < remain_cnt)
		{
			rra(ps);
			idx++;
		}
		ra(ps);
		sort_bigger(ps, remain_cnt - 1);
		rra(ps);
		sort_smaller(ps, n - remain_cnt);
		return (0);
	}
}

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

int	sort_smaller(t_stack *ps, int n)
{
	int pivot;
	int	remain_cnt;
	int	idx;

	if (ps == 0)
		return (-1);
	if (n <= 0)
		return (0);
	else if (n == 1)
	{
		if (pa(ps) < 0)
			printf("pa 에러\n");
		return (0);
	}
	else if (n == 2)
	{
		if (ps->top_b->data < ps->top_b->next->data)
		{
			if (sb(ps) < 0)
				printf("sb 에러\n");
		}
		if (pa(ps) < 0)
			printf("pa 에러\n");
		if (pa(ps) < 0)
			printf("pa 에러\n");
		return (0);
	}
	else
	{
		pivot = select_pivot_b(ps, n);
		remain_cnt = transfer_bigger_data_than_pivot(ps, n, pivot);
		idx = 0;
		while (idx < remain_cnt)
		{
			if (rrb(ps) < 0)
				printf("rrb 에러!!\n");
			idx++;
		}
		sort_bigger(ps, n - remain_cnt);
		/*
		if (rb(ps) < 0)
			printf("rb 에러!!\n");
		*/
		sort_smaller(ps, remain_cnt);
		return (0);
	}
}

