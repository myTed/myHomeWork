/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:51:21 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/27 19:26:12 by kyolee           ###   ########.fr       */
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
		int 	(*sa)(struct s_stack *s);
		int 	(*sb)(struct s_stack *s);
		int 	(*ss)(struct s_stack *s);
		int 	(*pa)(struct s_stack *s);
		int 	(*pb)(struct s_stack *s);
		int		(*ra)(struct s_stack *s);
		int		(*rb)(struct s_stack *s);
		int 	(*rr)(struct s_stack *s);
		int 	(*rra)(struct s_stack *s);
		int 	(*rrb)(struct s_stack *s);
		int 	(*rrr)(struct s_stack *s);
		int		(*init)(struct s_stack *s);
		int		(*insert)(struct s_stack *s, t_elem elem);
	} t_stack;
#endif
