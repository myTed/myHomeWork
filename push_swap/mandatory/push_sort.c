/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:56:02 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/30 21:54:37 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	select_pivot_a(t_stack *s, int n)
{
	return (s->top_a.data);
}

int	select_pivot_b(t_stack *s, int n)
{
	return (s->top_b.data);
}


int	transfer_data_small_than_pivot(t_stack *ps, int n, int pivot)
{
	int	idx;
	int	pb_cnt;

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

int	transfer_data_bigger_than_pivot(t_stack *ps, int n, int pivot)
{
	int	idx;
	int	pa_cnt;

	idx = 0;
	pb_cnt = 0;
	while (idx < n)
	{
		data = ps->top_b->data;
		if (data > pivot)
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

int	sort_bigger(t_stack *ps, int n)
{
	int	pivot;
	int	remain_cnt;

	if (n <= 1)
		return ;
	else if (n == 2)
	{
		if (ps->top_a->data > ps->top_a->next->data)
			sa(ps);
		return ;
	}
	else
	{
		pivot = select_pivot_a(ps, n);
		remain_cnt = transfer_small_data_than_pivot(ps, n, pivot);
		rra(remain_cnt);
		sort_bigger(remain_cnt);
		sort_smaller(n - remain_cnt);
	}
}

int	sort_smaller(t_stack *ps, int n)
{
	int pivot;
	int	remain_cnt;

	if (n <= 1)
	{
		pa(ps);
		return ;
	}
	else if (n == 2)
	{
		if (ps->top_b->data < ps->top->next->data)
			sb(ps);
		pa(ps);
		pa(ps);
		return ;
	}
	else
	{
		pivot = select_pivot_b(ps, n);
		remain_cnt = transfer_bigger_data_than_pivot(ps, n, pivot);
		rrb(remain_cnt);
		sort_bigger(n - remain_cnt);
		sort_smaller(remain_cnt);
	}
}

