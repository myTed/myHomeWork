/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:54:58 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 17:23:28 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>

int	init_stack_info(t_stack *s, t_select_stack *ps, t_partition_info *pi)
{
	if (s == 0)
		return (-1);
	ft_memset(s, 0, sizeof(t_stack));
	ft_memset(&ps->big, 0, sizeof(t_stack));
	ft_memset(&ps->medium, 0, sizeof(t_stack));
	ft_memset(&ps->small, 0, sizeof(t_stack));
	pi->first_partition = 1;
	return (0);
}

int	free_stack(t_stack *s)
{
	t_elem	data;

	if (s == 0)
		return (-1);
	while (s->top_a)
		pop(s, &s->top_a, &s->bottom_a, &data);
	while (s->top_b)
		pop(s, &s->top_b, &s->bottom_b, &data);
	return (0);
}

int	arg_pop(t_stack *s)
{
	return (free_stack(s));
}

/*
int	print_stack(t_list *ptop, t_list *pbottom)
{
	t_list *ptmp;
	
	if ((ptop == 0) || (pbottom == 0))
		return (-1);
	ptmp = ptop;
	do
	{
		printf("%d ", ptmp->data);
		ptmp = ptmp->next;
	} while (ptmp != ptop);
	return (0);
}
*/

int	main(int argc, char *argv[])
{
	t_stack				stack;
	t_select_stack		s_stack;
	t_partition_info	pi;
	int					start_idx;
	int					splited;

	if (argc < 2)
		return (0);
	if (init_stack_info(&stack, &s_stack, &pi) < 0)
		return (-1);
	start_idx = 1;
	splited = 0;
	if (arg_push(&stack, argv, start_idx, splited) < 0)
	{
		if (arg_pop(&stack) < 0)
			return (-1);
		write(2, "Error\n", ft_strlen("Error\n"));
		return (-1);
	}
	if (stack.a_data_cnt < 6)
		return (sort_size_under_handler(&stack, stack.a_data_cnt));
	else
		quick_sort_a(&s_stack, &stack, stack.a_data_cnt, &pi);
	/*
	print_stack(stack.top_a, stack.bottom_a);
	*/
	return (0);
}
