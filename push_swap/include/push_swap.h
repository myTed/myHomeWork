/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/13 16:24:46 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

#ifndef PUSH_SWAP_H
 #define PUSH_SWAP_H
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
		size_t	big_cnt;
		size_t	medium_cnt;
		size_t	small_cnt;
	} t_select_stack;

	typedef struct s_pivot
	{
		t_elem one_third_pivot;
		t_elem two_third_pivot;
	} t_pivot;

	typedef struct s_partition_info
	{
		t_pivot	pv;
		int	partioned;
		int	ra_cnt;
		int	skip_ra_cnt;
		int	rb_cnt;
		int	skip_rb_cnt;
		int	pb_cnt;
		int	pa_cnt;
	} t_partition_info;



int	arg_push(t_stack *ps, char *argv[], int idx, int splited);
long long int ft_atol(const char *str, int *poverflow);
int	push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom);
int	push_bottom(t_stack *s, t_elem elem);
int	pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata);
int	sort_bigger(t_select_stack *pss, t_stack *ps, int n);
int	sort_smaller(t_select_stack *pss, t_stack *ps, int n);
t_elem	quick_select(t_select_stack *psel, t_list *top, size_t order, size_t size);
int	sort_n2_div_2(t_stack *ps, t_list *ptop, int b_stack_a, int n);

int	sort_size_3_small(t_stack *ps, t_list *ptop);
int	free_stack(t_stack *s);


int	quick_sort_a(t_select_stack *pss, t_stack *ps, int n, int b_first_sort);
int	quick_sort_b(t_select_stack *pss, t_stack *ps, int n, int b_first_sort);
int	free_split(char **str);
int	malloc_arg_check(char *str, char ***psplit_argv, int *psplited);
int	is_already_ordered_stack_a(t_stack *ps, int n);
int	sort_size_under_handler(t_stack *ps,int size);
int	find_maximum_value_idx(t_list *ptop, int n, int *pmax_idx);
int	find_minimum_value_idx(t_list *ptop, int n, int *pmin_idx);
int	sort_size_2_big(t_stack *ps);
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
