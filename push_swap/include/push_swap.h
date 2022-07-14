/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:45:09 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>

typedef int	t_elem;
typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	t_elem			data;
}	t_list;

typedef struct s_stack
{
	t_list	*top_a;	
	t_list	*top_b;
	t_list	*bottom_a;
	t_list	*bottom_b;
	size_t	a_data_cnt;
	size_t	b_data_cnt;
}	t_stack;

typedef struct s_select
{
	t_stack	big;
	t_stack	medium;
	t_stack	small;
	size_t	big_cnt;
	size_t	medium_cnt;
	size_t	small_cnt;
}	t_select_stack;

typedef struct s_pivot
{
	t_elem	one_third_pivot;
	t_elem	two_third_pivot;
}	t_pivot;

typedef struct s_partition_info
{
	t_pivot	pv;
	int		first_partition;
	int		ra_cnt;
	int		skip_ra_cnt;
	int		rb_cnt;
	int		skip_rb_cnt;
	int		pb_cnt;
	int		pa_cnt;
}	t_partition_info;

long long int	ft_atol(const char *str, int *poverflow);
int				arg_push(t_stack *ps, char *argv[], int idx, int splited);
int				is_already_ordered_stack_a(t_stack *ps, int n);
int				is_already_ordered_stack_b(t_stack *ps, int n);
int				push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom);
int				push_bottom(t_stack *s, t_elem elem);
int				pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata);
int				sort_size_3_under_b(t_stack *ps, int n);
int				sort_size_3_under_a(t_stack *ps, int n);
int				free_stack(t_stack *s);
int				quick_sort_a(t_select_stack *pss, t_stack *ps,
					int n, t_partition_info *pi);
int				quick_sort_b(t_select_stack *pss, t_stack *ps,
					int n, t_partition_info *pi);
int				free_split(char **str);
int				malloc_arg_check(char *str, char ***psplit_argv, int *psplited);
int				sort_size_under_handler(t_stack *ps, int size);
int				find_maximum_value_idx(t_list *ptop, int n, int *pmax_idx);
int				find_minimum_value_idx(t_list *ptop, int n, int *pmin_idx);
int				select_pivot(t_select_stack *pss, t_list *ptop, int size,
					t_pivot *ppv);
int				sort_size_2_big(t_stack *ps);
int				divide_partition_a(
					t_select_stack *pss,
					t_stack *ps,
					int n,
					t_partition_info *ppi
					);
int				divide_partition_stack_b(
					t_select_stack *pss,
					t_stack *ps,
					int n,
					t_partition_info *ppi
					);
t_elem			quick_select(
					t_select_stack *psel,
					t_list *top,
					size_t order,
					size_t size
					);
int				first_transfer_smaller_data_than_two_third_pivot(
					t_stack *ps,
					int n,
					t_partition_info *ppi
					);
int				transfer_smaller_data_than_two_third_pivot(
					t_stack *ps,
					int n,
					t_partition_info *ppi
					);
int				transfer_bigger_data_than_pivot(t_stack *ps, int n, int pivot);
int				transfer_bigger_data_than_one_third_pivot(
					t_stack *ps,
					int n,
					t_partition_info *ppi
					);
int				roll_back_stack(t_stack *ps, t_partition_info *ppi);
int				is_only_data_more_than_two_third_pivot(
					t_stack *ps,
					t_pivot *ppv,
					int start_idx,
					int end_idx
					);
int				is_only_data_less_than_one_third_pivot(
					t_stack *ps,
					t_pivot *ppv,
					int start_idx,
					int end_idx
					);
int				sa(t_stack *ps);
int				sb(t_stack *ps);
int				ss(t_stack *ps);
int				pa(t_stack *ps);
int				pb(t_stack *ps);
int				ra(t_stack *ps);
int				rb(t_stack *ps);
int				rr(t_stack *ps);
int				rra(t_stack *ps);
int				rrb(t_stack *ps);
int				rrr(t_stack *ps);
#endif
