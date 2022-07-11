/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:56:02 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/11 01:18:21 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
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
/*
int	find_minimum_value_idx(t_list *ptop, int n, int *pmin_idx)
{
	int		idx;
	t_list 	*tmp_top;
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
*/
int	sort_size_2_big(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (ps->top_a->data > ps->top_a->next->data)
		sa(ps);
	return (0);
}

int sort_size_2_small(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (ps->top_b->data < ps->top_b->next->data)
		sb(ps);
	return (0);
}


int	sort_size_3_under_big(t_stack *ps, t_list *ptop, int n)
{
	int	max_idx;

	if ((ptop == 0) || (ptop == 0))
		return (-1);
	if (n == 2)
	{
		if (sort_size_2_big(ps) < 0)
			return (-1);
	}
	else
	{
		if (find_maximum_value_idx(ptop, n, &max_idx) < 0)
			return (-1);
		if (max_idx == n - 1)
		{
			if (sort_size_2_big(ps) < 0)
				return (-1);
		}
		else
		{
			if (ps->top_a->data > ps->top_a->next->data)
				sa(ps);
			pb(ps);
			if (sort_size_2_big(ps) < 0)
				return (-1);
			pa(ps);
			if (sort_size_2_big(ps) < 0)
				return (-1);
		}	
	}
	return (0);
}

int	sort_size_3_under_small(t_stack *ps, t_list *ptop, int n)
{
	int	max_idx;

	if (ptop == 0)
		return (-1);
	if (n == 2)
	{
		if (sort_size_2_small(ps) < 0)
			return (-1);
		pa(ps);
		pa(ps);
	}
	else
	{
		if (find_maximum_value_idx(ptop, n, &max_idx) < 0)
			return (-1);
		if (max_idx == 0)
		{
			pa(ps);
			if (sort_size_2_small(ps) < 0)
				return (-1);
			pa(ps);
			pa(ps);
		}
		else
		{
			if (ps->top_b->data < ps->top_b->next->data)
				sb(ps);
			pa(ps);	
			if (sort_size_2_small(ps) < 0)
				return (-1);
			pa(ps);
			if (sort_size_2_big(ps) < 0)
				return (-1);
			pa(ps);
		}
	}
	return (0);
}


int	sort_size_4_under_small(t_stack *ps, t_list *ptop, int n)
{
	t_select_stack 	sls;
	t_elem			m_pivot;
	int				pa_cnt;
	int				rb_cnt;
	int				idx;

	if ((ps == 0) || (ptop == 0))
		return (-1);
	ft_memset(&sls, 0, sizeof(t_select_stack));
	m_pivot = quick_select(&sls, ptop, 2, n);
	free_stack(&(sls.big));
	free_stack(&(sls.medium));
	free_stack(&(sls.small));
	idx = 0;
	pa_cnt = 0;
	rb_cnt = 0;
	while ((idx < n) && (pa_cnt < 2))
	{
		if (ps->top_b->data > m_pivot)
		{
			pa(ps);
			pa_cnt++;
		}
		else
		{
			rb(ps);
			rb_cnt++;
		}
		idx++;
	}
	idx = 0;
	while (idx < rb_cnt)
	{
		rrb(ps);
		idx++;
	}
	if (ps->top_b->data < ps->top_b->next->data)
	{
		if (ps->top_a->data > ps->top_a->next->data)
			ss(ps);
		else
			sb(ps);
	}
	else
	{
		if (ps->top_a->data > ps->top_a->next->data)
			sa(ps);
	}
	pa(ps);
	pa(ps);
	return (0);
}


int	sort_size_4_under_big(t_stack *ps, t_list *ptop, int n)
{
	t_select_stack 	sls;
	t_elem			m_pivot;
	int				pb_cnt;
	int				ra_cnt;
	int				idx;

	if ((ps == 0) || (ptop == 0))
		return (-1);
	ft_memset(&sls, 0, sizeof(t_select_stack));
	m_pivot = quick_select(&sls, ptop, 3, n);
	free_stack(&(sls.big));
	free_stack(&(sls.medium));
	free_stack(&(sls.small));
	idx = 0;
	pb_cnt = 0;
	ra_cnt = 0;
	while ((idx < n ) && (pb_cnt < 2))
	{
		if (ps->top_a->data < m_pivot)
		{
			pb(ps);
			pb_cnt++;
		}
		else
		{
			ra(ps);
			ra_cnt++;
		}
		idx++;
	}
	idx = 0;
	while (idx < ra_cnt)
	{
		rra(ps);
		idx++;
	}
	if (ps->top_a->data > ps->top_a->next->data)
	{
		if (ps->top_b->data < ps->top_b->next->data)
			ss(ps);
		else
			sa(ps);
	}
	else
	{
		if (ps->top_b->data < ps->top_b->next->data)
			sb(ps);
	}
	pa(ps);
	pa(ps);
	return (0);
}


int	sort_size_6_under_big(t_stack *ps, t_list *ptop, int n)
{
	t_select_stack 	ss;
	t_elem			m_pivot;
	int				pb_cnt;
	int				ra_cnt;
	int				idx;

	if ((ps == 0) || (ptop == 0))
		return (-1);
	ft_memset(&ss, 0, sizeof(t_select_stack));
	m_pivot = quick_select(&ss, ptop, 4, n);
	free_stack(&(ss.big));
	free_stack(&(ss.medium));
	free_stack(&(ss.small));
	idx = 0;
	pb_cnt = 0;
	ra_cnt = 0;
	while ((idx < n) && (pb_cnt < 3))
	{
		if (ps->top_a->data < m_pivot)
		{
			pb(ps);
			pb_cnt++;
		}
		else
		{
			ra(ps);
			ra_cnt++;
		}
		idx++;
	}
	idx = 0;
	while (idx < ra_cnt)
	{
		rra(ps);
		idx++;
	}
	printf("---------------\n");
	if (sort_size_3_under_big(ps, ps->top_a, 3) < 0)
		return (-1);
	printf("---------------\n");
	if (sort_size_3_under_small(ps, ps->top_b, 3) < 0)
		return (-1);
	return (0);
}


int sort_size_5_under_big(t_stack *ps, t_list *ptop, int n)
{
	t_select_stack 	ss;
	t_elem			m_pivot;
	int				pb_cnt;
	int				ra_cnt;
	int				idx;

	if ((ps == 0) || (ptop == 0))
		return (-1);
	//fprintf(stderr, "sort size 5====");
	ft_memset(&ss, 0, sizeof(t_select_stack));
	m_pivot = quick_select(&ss, ptop, 3, n);
	free_stack(&(ss.big));
	free_stack(&(ss.medium));
	free_stack(&(ss.small));
	idx = 0;
	pb_cnt = 0;
	ra_cnt = 0;
	while ((idx < n) && (pb_cnt < 2))
	{
		if (ps->top_a->data < m_pivot)
		{
			pb(ps);
			pb_cnt++;
		}
		else
		{
			ra(ps);
			ra_cnt++;
		}
		idx++;
	}
	idx = 0;
	while (idx < ra_cnt)
	{
		rra(ps);
		idx++;
	}
	if (sort_size_3_under_big(ps, ps->top_a, 3) < 0)
		return (-1);
	if (sort_size_2_small(ps) < 0)
		return (-1);
	pa(ps);
	pa(ps);
	return (0);
}


int	sort_size_5_under_small(t_stack *ps, t_list *ptop, int n)
{
	t_select_stack	ss;
	t_elem			m_pivot;
	int				pa_cnt;
	int				rb_cnt;
	int				idx;

	if ((ps == 0) || (ptop == 0))
		return (-1);
	ft_memset(&ss, 0, sizeof(t_select_stack));
	m_pivot = quick_select(&ss, ptop, 3, n);
	free_stack(&(ss.big));
	free_stack(&(ss.medium));
	free_stack(&(ss.small));
	idx = 0;
	pa_cnt = 0;
	rb_cnt = 0;
	while ((idx < n) && (pa_cnt < 2))
	{
		if (ps->top_b->data > m_pivot)
		{
			pa(ps);
			pa_cnt++;
		}
		else
		{
			rb(ps);
			rb_cnt++;
		}
		idx++;
	}
	idx = 0;
	while (idx < rb_cnt)
	{
		rrb(ps);
		idx++;
	}
	if (sort_size_2_big(ps) < 0)
		return (-1);
	if (sort_size_3_under_small(ps, ps->top_b, 3) < 0)
		return (-1);
	return (0);
}

int	select_pivot(t_select_stack *pss, t_list *ptop, int size, t_pivot *ppv)
{
	if ((pss == 0) || (ptop == 0))
		return (-1);
	ppv->one_third_pivot = quick_select(pss, ptop, ((double)size / 3), size);
	ppv->two_third_pivot = quick_select(pss, ptop, (((double)size * 2) / 3), size);
	free_stack(&(pss->big));
	free_stack(&(pss->medium));
	free_stack(&(pss->small));
	return (0);
}



int	is_only_data_more_than_two_third_pivot(t_stack *ps, t_pivot *ppv, int	start_idx, int end_idx)
{
	int	idx;
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

int	is_only_data_less_than_one_third_pivot(t_stack *ps, t_pivot *ppv, int start_idx, int end_idx)
{
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


int transfer_final_data_smaller_two_third_pivot(t_stack *ps, t_pivot *ppv, t_partition_info *ppi)
{
	if ((ps == 0) || (ppv == 0) || (ppi == 0))
		return (-1);
	if ((ps->top_a->next->data < ppv->two_third_pivot))
	{
		sa(ps);
		ppi->skip_ra_cnt++;
		pb(ps);
		ppi->pb_cnt++;
		if (ps->top_b->data >= ppv->one_third_pivot)
		{
			rb(ps);
			ppi->rb_cnt++;
		}
		return (1);
	}
	return (0);
}


int	first_transfer_smaller_data_than_two_third_pivot(
		t_stack				*ps,
		int					n,
		t_pivot				*ppv,
		t_partition_info	*ppi
){
	int	idx;

	if ((ps == 0) || (ppv == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	while (idx < n)
	{
		if (is_only_data_more_than_two_third_pivot(ps, ppv, idx, n) == 1)
		{
			ppi->skip_ra_cnt = n - idx;
			return (0);
		}
		if (ps->top_a->data >= ppv->two_third_pivot)
		{
			ra(ps);
			ppi->ra_cnt++;
		}
		else
		{
			pb(ps);
			ppi->pb_cnt++;
			if (ps->top_b->data < ppv->one_third_pivot)
				rb(ps);
			else
				ppi->rb_cnt++;
		}
		idx++;
	}
	return (0);
}



int	transfer_smaller_data_than_two_third_pivot(
		t_stack 			*ps,
		int 				n, 
		t_pivot				*ppv,
		t_partition_info 	*ppi
){
	int		idx;

	if ((ps == 0) || (ppv == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	while (idx < n)
	{
		if (is_only_data_more_than_two_third_pivot(ps, ppv, idx, n) == 1)
		{
			ppi->skip_ra_cnt = n - idx;
			return (0);
		}
		if (ps->top_a->data >= ppv->two_third_pivot)
		{
			if (idx == n - 2)
			{
				if (transfer_final_data_smaller_two_third_pivot(ps, ppv, ppi) == 1)
					return (0);
			}
			ra(ps);
			ppi->ra_cnt++;
		}
		else
		{
			pb(ps);
			ppi->pb_cnt++;
			if (ps->top_b->data >= ppv->one_third_pivot)
			{
				rb(ps);
				ppi->rb_cnt++;
			}
		}
		idx++;
	}
	return (0);
}

int transfer_final_data_bigger_one_third_pivot(t_stack *ps, t_pivot *ppv, t_partition_info *ppi)
{
	if ((ps == 0) || (ppv == 0) || (ppi == 0))
		return (-1);
	if ((ps->top_b->next->data >= ppv->one_third_pivot))
	{
		sb(ps);
		ppi->skip_rb_cnt++;
		pa(ps);
		ppi->pa_cnt++;
		if (ps->top_a->data < ppv->two_third_pivot)
		{
			ra(ps);
			ppi->ra_cnt++;
		}
		return (1);
	}
	return (0);
}

int	transfer_bigger_data_than_one_third_pivot(
		t_stack	*ps,
		int		n,
		t_pivot	*ppv,
		t_partition_info *ppi
){
	int		idx;
	
	if ((ps == 0) || (ppv == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	while (idx < n)
	{
		if (is_only_data_less_than_one_third_pivot(ps, ppv, idx, n) == 1)
		{
			ppi->skip_rb_cnt = n - idx;
			return (0);
		}
		if (ps->top_b->data < ppv->one_third_pivot)
		{
			if (idx == n - 2)
			{
				if (transfer_final_data_bigger_one_third_pivot(ps, ppv, ppi) == 1)
					return (0);
			}
			rb(ps);
			ppi->rb_cnt++;
		}
		else
		{
			pa(ps);
			ppi->pa_cnt++;
			if (ps->top_a->data < ppv->two_third_pivot)
			{
				ra(ps);
				ppi->ra_cnt++;
			}
		}
		idx++;
	}
	return (0);
}


int	first_divide_partition_stack_a(
		t_select_stack *pss,
		t_stack *ps,
		int	n,
		t_partition_info *ppi
){
	if ((pss == 0) || (ps == 0) || (ppi == 0))
		return (-1);
	ft_memset(ppi, 0, sizeof(t_partition_info));
	if (select_pivot(pss, ps->top_a, n , &(ppi->pv)) < 0)
		return (-1);
	if (first_transfer_smaller_data_than_two_third_pivot(ps, n, &(ppi->pv), ppi) < 0)
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
	if (transfer_smaller_data_than_two_third_pivot(ps, n, &(ppi->pv), ppi) < 0)
		return (-1);
	return (0);
}


int	divide_partition_stack_b(
		t_select_stack *pss,
		t_stack *ps,
		int	n,
		t_partition_info *ppi
){
	if ((pss == 0) || (ps == 0) || (ppi == 0))
		return (-1);
	ft_memset(ppi, 0, sizeof(t_partition_info));
	if (select_pivot(pss, ps->top_b, n, &(ppi->pv)) < 0)
		return (-1);
	if (transfer_bigger_data_than_one_third_pivot(ps, n, &(ppi->pv), ppi) < 0)
		return (-1);
	return (0);
}


int	roll_back_stack_common(t_stack *ps, t_partition_info *ppi, int *prrr_cnt)
{
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
	int			common_rrr_cnt;
	int			idx;

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


int	roll_back_stack_2(t_stack *ps, t_partition_info *ppi)
{
	int	idx;
	//int	cnt;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	//cnt = 0;
	while (idx < ppi->ra_cnt)
	{
		rra(ps);
		/*
		if ((cnt == 0) && (ps->top_a->data == ppi->pv.two_third_pivot))
		{
			pb(ps);
			cnt = 1;
		}
		*/
		idx++;
	}
	return (0);
}

int	roll_back_stack_3(t_stack *ps, t_partition_info *ppi)
{
	int	idx;
	//int	cnt;

	if ((ps == 0) || (ppi == 0))
		return (-1);
	idx = 0;
	//cnt = 0;
	while (idx < ppi->rb_cnt)
	{
		rrb(ps);
		/*
		if ((cnt == 0) && (ps->top_b->data == ppi->pv.one_third_pivot))
		{
			pa(ps);
			ra(ps);
			cnt = 1;
		}
		*/
		idx++;
	}
	return (0);
}


int	is_already_ordered_stack_a(t_stack *ps, int n)
{
	int	idx;
	t_list *ptmp_top;

	if (ps == 0)
		return (-1);
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
	int	idx;
	t_list	*ptmp_top;

	if (ps == 0)
		return (-1);
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

int	quick_sort_b(t_select_stack *pss, t_stack *ps, int n, int b_first_sort)
{
	t_partition_info 	pi;
	int					idx;	
	
	if ((pss == 0) || (ps == 0))
		return (-1);
	//fprintf(stderr, "sortb ====== n ==== : %d\n",n);
	if (n <= 0)
		return (0);
	if (n == 1)
	{
		pa(ps);
		return (0);
	}
	if (is_already_ordered_stack_b(ps, n))
	{
		idx = 0;
		while (idx < n)
		{
			pa(ps);
			idx++;
		}
		return (0);
	}
	else if (n == 5)
	{
		if (sort_size_5_under_small(ps, ps->top_b, n) < 0)
			return (-1);
	}
	else if (n == 4)
	{
		if (sort_size_4_under_small(ps, ps->top_b, n) < 0)
			return (-1);
	}
	else if ((n == 2) || (n == 3))
	{
		if (sort_size_3_under_small(ps, ps->top_b, n) < 0)
			return (-1);
	}
	else
	{
		
		if (divide_partition_stack_b(pss, ps, n , &pi) < 0)
			return (-1);
		quick_sort_a(pss, ps, pi.pa_cnt - pi.ra_cnt, b_first_sort);
		if (roll_back_stack(ps, &pi) < 0)
			return (-1);
		quick_sort_a(pss, ps, pi.ra_cnt, b_first_sort);
		quick_sort_b(pss, ps, pi.rb_cnt + pi.skip_rb_cnt, b_first_sort);
	}
	return (0);
}




int	quick_sort_a(t_select_stack *pss, t_stack *ps, int n, int b_first_sort)
{
	t_partition_info 	pi;

	if ((pss == 0) || (ps == 0))
		return (-1);
	if (n <= 1)
		return (0);
	if (is_already_ordered_stack_a(ps, n))
		return (0);
	if (n == 5)
	{
		if (sort_size_5_under_big(ps, ps->top_a, n) < 0)
			return (-1);
	}
	else if (n == 4)
	{
		if (sort_size_4_under_big(ps, ps->top_a, n) < 0)
			return (-1);
	}	
	else if ((n == 2) || (n == 3))
	{
		if (sort_size_3_under_big(ps, ps->top_a, n) < 0)
			return (-1);
	}
	else
	{
		if (b_first_sort)
		{
			if (first_divide_partition_stack_a(pss, ps, n , &pi) < 0)
				return (-1);
			b_first_sort = 0;
		}
		else
		{	
			if (divide_partition_stack_a(pss, ps, n, &pi) < 0)
				return (-1);
		/*
		if (roll_back_stack(ps, &pi) < 0)
			return (-1);
		*/

		/*
		if (roll_back_stack_2(ps, &pi) < 0)
			return (-1);
		quick_sort_a(pss, ps, pi.ra_cnt - 1);
		pa(ps);
		if (roll_back_stack_3(ps, &pi) < 0)
			return (-1);
		quick_sort_b(pss, ps, pi.rb_cnt - 1);
		rra(ps);
		quick_sort_b(pss, ps, pi.pb_cnt - pi.rb_cnt);
		*/
		/*
		if (roll_back_stack_2(ps, &pi) < 0)
			return (-1);
		if (roll_back_stack_3(ps, &pi) < 0)
			return (-1);
		*/
			if (roll_back_stack(ps, &pi) < 0)
				return (-1);
		}
		quick_sort_a(pss, ps, pi.ra_cnt + pi.skip_ra_cnt, b_first_sort);
		quick_sort_b(pss, ps, pi.rb_cnt, b_first_sort);
		quick_sort_b(pss, ps, pi.pb_cnt - pi.rb_cnt, b_first_sort);
	}
	return (0);
}


/*
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
		if (sort_size_2_big(ps) < 0)
			return (-1);
	}
	else if (n == 3)
	{
		if (sort_size_3_big(ps, ps->top_a) < 0)
			return (-1);
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
	}
	return (0);
}
*/

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
/*
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
		if (sort_size_2_small(ps) < 0)
			return (-1);
		if (pa(ps) < 0)
			printf("pa 에러\n");
		if (pa(ps) < 0)
			printf("pa 에러\n");
		return (0);
	}
	else if (n == 3)
	{
		if (sort_size_3_small(ps, ps->top_b) < 0)
			return (-1);
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
		sort_smaller(pss, ps, remain_cnt);
		return (0);
	}
}
*/
