/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/28 21:08:58 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	} t_stack;

int	push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom);
int	pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata);
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
