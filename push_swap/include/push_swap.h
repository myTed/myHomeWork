/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/11 00:47:36 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

#ifndef PUSH_SWAP_H
 #define PUSH_SWAP_H
 #define	SORT_STACK_A	1
 #define	SORT_STACK_B	0
	typedef int	t_elem;
	typedef struct s_list
	{
		struct s_list *prev;
		struct s_list *next;
		t_elem	data;
	} t_list;

	typedef struct s_stack
	{
		t_list	*top_a;	
		t_list	*top_b;
		t_list	*bottom_a;
		t_list	*bottom_b;
		size_t	a_data_cnt;
		size_t	b_data_cnt;
	} t_stack;

	typedef struct s_select
	{
		t_stack big;
		t_stack medium;
		t_stack small;
	} t_select_stack;

	typedef struct s_pivot
	{
		t_elem one_third_pivot;
		t_elem two_third_pivot;
	} t_pivot;

	typedef struct s_partition_info
	{
		t_pivot	pv;
		int	ra_cnt;
		int	skip_ra_cnt;
		int	rb_cnt;
		int	skip_rb_cnt;
		int	pb_cnt;
		int	pa_cnt;
	} t_partition_info;




int	push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom);
int	pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata);
int	sort_bigger(t_select_stack *pss, t_stack *ps, int n);
int	sort_smaller(t_select_stack *pss, t_stack *ps, int n);
t_elem	quick_select(t_select_stack *psel, t_list *top, size_t order, size_t size);
int	sort_n2_div_2(t_stack *ps, t_list *ptop, int b_stack_a, int n);

int	sort_size_3_small(t_stack *ps, t_list *ptop);
int	free_stack(t_stack *s);


int	quick_sort_a(t_select_stack *pss, t_stack *ps, int n, int b_first_sort);
int	quick_sort_b(t_select_stack *pss, t_stack *ps, int n, int b_first_sort);

int	sa(t_stack *ps);
int	sb(t_stack *ps);
int	ss(t_stack *ps);
int	pa(t_stack *ps);
int	pb(t_stack *ps);
int	ra(t_stack *ps);
int	rb(t_stack *ps);
int	rr(t_stack *ps);
int rra(t_stack *ps);
int	rrb(t_stack *ps);
int	rrr(t_stack *ps);
#endif