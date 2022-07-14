/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:10:36 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:10:37 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	partition_quick_select(t_elem pivot, t_list *top, t_select_stack *psel)
{
	if ((psel == 0) || (top == 0))
		return (-1);
	if (top->data < pivot)
	{
		push(&(psel->small), top->data, &(psel->small.top_a),
			&(psel->small.bottom_a));
		psel->small_cnt++;
	}
	else if (top->data > pivot)
	{
		push(&(psel->big), top->data, &(psel->big.top_a),
			&(psel->big.bottom_a));
		psel->big_cnt++;
	}
	else
	{
		push(&(psel->medium), top->data, &(psel->medium.top_a),
			&(psel->medium.bottom_a));
		psel->medium_cnt++;
	}
	return (0);
}

t_elem	quick_select(
	t_select_stack *psel,
	t_list *top,
	size_t order,
	size_t size
){
	t_list	*tmp_top;
	t_elem	pivot;
	size_t	idx;

	tmp_top = top;
	pivot = tmp_top->next->data;
	idx = 0;
	psel->big_cnt = 0;
	psel->medium_cnt = 0;
	psel->small_cnt = 0;
	while (idx < size)
	{
		if (partition_quick_select(pivot, tmp_top, psel) < 0)
			return (-1);
		idx++;
		tmp_top = tmp_top->next;
	}
	if (psel->small_cnt >= order)
		return (quick_select(psel, psel->small.top_a, order, psel->small_cnt));
	else if (psel->small_cnt + psel->medium_cnt < order)
		return (quick_select(psel, psel->big.top_a,
				order - psel->small_cnt - psel->medium_cnt,
				psel->big_cnt));
	else
		return (pivot);
}

int	select_pivot(t_select_stack *pss, t_list *ptop, int size, t_pivot *ppv)
{
	if ((pss == 0) || (ptop == 0))
		return (-1);
	ppv->one_third_pivot = quick_select(pss, ptop,
			((double)size / 3), size);
	ppv->two_third_pivot = quick_select(pss, ptop,
			(((double)size * 2) / 3), size);
	free_stack(&(pss->big));
	free_stack(&(pss->medium));
	free_stack(&(pss->small));
	return (0);
}
