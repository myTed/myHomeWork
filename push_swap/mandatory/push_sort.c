/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:56:02 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/06 02:35:35 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include <stdio.h>

int	find_maximum_value_idx(t_list *ptop, int n, int *pmax_idx)
{
	int		idx;
	t_list 	*tmp_top;
	t_elem	max_value;
	
	if (ptop == 0)
		return (-1);
	tmp_top = ptop;
	max_value = tmp_top->data;
	*pmax_idx = 0;
	idx = 0;
	while (idx < n - 1)
	{
		tmp_top = tmp_top->next;
		if (tmp_top->data > max_value)
		{
			max_value = tmp_top->data;
			(*pmax_idx)++;
		}
		idx++;
	}
	return (0);
}

int	sort_n2_div_2(t_stack *ps, t_list *ptop, int b_stack_a, int n)
{
	int	max_idx;
	int	idx;

	if (ptop == 0)
		return (-1);
	if (n == 2)
	{
		if (ptop->data > ptop->next->data)
		{
			if (b_stack_a)
				sa(ps);
			else
				sb(ps);
		}
		return (0);
	}
	else
	{
		if (find_maximum_value_idx(ptop, n, &max_idx) < 0)
			return (-1);
		idx = 0;
		if (b_stack_a)
		{
			while(idx < n - max_idx - 1)
			{
				rra(ps);
				idx++;
			}
			ptop = ps->top_a;
		}
		else
		{
			while(idx < n - max_idx -1)
			{
				rrb(ps);
				idx++;
			}
			ptop = ps->top_b;
		}
		sort_n2_div_2(ps, ptop, b_stack_a, n - 1);
	}
	return (0);
}


int	select_pivot(t_select_stack *pss, t_list *ptop, int size, t_elem *ppivot)
{
	if ((pss == 0) || (ptop == 0))
		return (-1);
	*ppivot = quick_select(pss, ptop, size / 2, size);
	free_stack(&(pss->big));
	free_stack(&(pss->medium));
	free_stack(&(pss->small));
	return (0);
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

int	sort_bigger(t_select_stack *pss, t_stack *ps, int n)
{
	int	pivot;
	int	remain_cnt;
	int	idx;
	int	trans_pivot_cnt;

	trans_pivot_cnt = 0;
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
		if (select_pivot(pss, ps->top_a, n, &pivot) < 0)
			return (-1);
		remain_cnt = transfer_smaller_data_than_pivot(ps, n, pivot);
		idx = 0;
		while (idx < remain_cnt)
		{
			rra(ps);
			if ((ps->top_a->data == pivot) && (trans_pivot_cnt == 0))
			{
				trans_pivot_cnt = 1;
				pb(ps);
			}
			idx++;
		}
		sort_bigger(pss, ps, remain_cnt - 1);
		pa(ps);
		sort_smaller(pss, ps, n - remain_cnt);
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

int	sort_smaller(t_select_stack *pss, t_stack *ps, int n)
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
		if (select_pivot(pss, ps->top_b, n, &pivot) < 0)
			return (-1);
		remain_cnt = transfer_bigger_data_than_pivot(ps, n, pivot);
		idx = 0;
		while (idx < remain_cnt)
		{
			if (rrb(ps) < 0)
				printf("rrb 에러!!\n");
			idx++;
		}
		sort_bigger(pss, ps, n - remain_cnt);
		/*
		if (rb(ps) < 0)
			printf("rb 에러!!\n");
		*/
		sort_smaller(pss, ps, remain_cnt);
		return (0);
	}
}

