/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:56:02 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 17:21:34 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <stdio.h>

int	roll_back_stack_common(
		t_stack *ps,
		t_partition_info *ppi,
		int *prrr_cnt
){
	int	idx;
	int	common_rrr_cnt;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	if (ppi->ra_cnt > ppi->rb_cnt)
		common_rrr_cnt = ppi->rb_cnt;
	else
		common_rrr_cnt = ppi->ra_cnt;
	idx = 0;
	while (idx < common_rrr_cnt)
	{
		rrr(ps);
		idx++;
	}
	*prrr_cnt = common_rrr_cnt;
	return (0);
}

int	roll_back_stack(t_stack *ps, t_partition_info *ppi)
{
	int	common_rrr_cnt;
	int	idx;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	common_rrr_cnt = 0;
	if (roll_back_stack_common(ps, ppi, &common_rrr_cnt) < 0)
		return (-1);
	idx = 0;
	while (idx < ppi->ra_cnt - common_rrr_cnt)
	{
		rra(ps);
		idx++;
	}
	idx = 0;
	while (idx < ppi->rb_cnt - common_rrr_cnt)
	{
		rrb(ps);
		idx++;
	}
	return (0);
}

int	push_a_continue(t_stack *ps, int n)
{
	int	idx;

	if (ps == 0)
		return (-1);
	idx = 0;
	while (idx < n)
	{
		pa(ps);
		idx++;
	}
	return (0);
}

int	quick_sort_b(
	t_select_stack *pss,
	t_stack *ps,
	int n,
	t_partition_info *ppi
){
	t_partition_info	pi;

	if ((pss == 0) || (ps == 0))
		return (-1);
	if (n <= 0)
		return (0);
	if (n <= 1)
	{
		pa(ps);
		return (0);
	}
	if (is_already_ordered_stack_b(ps, n))
		return (push_a_continue(ps, n));
	if (n <= 3)
		return (sort_size_3_under_b(ps, n));
	if (divide_partition_stack_b(pss, ps, n, ppi) < 0)
		return (-1);
	pi = *ppi;
	quick_sort_a(pss, ps, pi.pa_cnt - pi.ra_cnt, ppi);
	if (roll_back_stack(ps, &pi) < 0)
		return (-1);
	quick_sort_a(pss, ps, pi.ra_cnt, ppi);
	quick_sort_b(pss, ps, pi.rb_cnt + pi.skip_rb_cnt, ppi);
	return (0);
}

int	quick_sort_a(
		t_select_stack *pss,
		t_stack *ps,
		int n,
		t_partition_info *ppi
){
	t_partition_info	pi;

	if ((pss == 0) || (ps == 0))
		return (-1);
	if (n <= 1)
		return (0);
	if (is_already_ordered_stack_a(ps, n))
		return (0);
	if (n <= 3)
		return (sort_size_3_under_a(ps, n));
	if (divide_partition_a(pss, ps, n, ppi) < 0)
		return (-1);
	pi = *ppi;
	quick_sort_a(pss, ps, pi.ra_cnt + pi.skip_ra_cnt, ppi);
	quick_sort_b(pss, ps, pi.rb_cnt, ppi);
	quick_sort_b(pss, ps, pi.pb_cnt - pi.rb_cnt, ppi);
	return (0);
}

