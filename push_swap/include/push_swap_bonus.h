/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/15 19:29:19 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H
# include <stddef.h>
# define PUSH_BUFF_SIZE	8

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

long long int	ft_atol(const char *str, int *poverflow);
int				arg_push(t_stack *ps, char *argv[], int idx, int splited);
int				is_already_ordered_stack_a(t_stack *ps, int n);
int				push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom);
int				push_bottom(t_stack *s, t_elem elem);
int				pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata);
int				free_stack(t_stack *s);
int				free_split(char **str);
int				malloc_arg_check(char *str, char ***psplit_argv, int *psplited);
int				read_operation(t_stack *ps);
int				is_sorted_stack(t_stack *ps, size_t unordered_cnt);
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
