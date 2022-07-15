/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 07:54:24 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/13 15:30:45 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>

int	rr(t_stack *ps)
{
	int	command_cnt;

	if (ps == 0)
		return (-1);
	command_cnt = 0;
	if ((ps->bottom_a != 0) && (ps->top_a != 0))
	{
		ps->bottom_a = ps->top_a;
		ps->top_a = ps->top_a->next;
		command_cnt++;
	}
	if ((ps->bottom_b != 0) && (ps->top_b != 0))
	{
		ps->bottom_b = ps->top_b;
		ps->top_b = ps->top_b->next;
		command_cnt++;
	}
	if (command_cnt == 0)
		return (0);
	return (0);
}

int	rra(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->top_a == 0) || (ps->bottom_a == 0))
		return (-2);
	ps->top_a = ps->bottom_a;
	ps->bottom_a = ps->bottom_a->prev;
	return (0);
}

int	rrb(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->top_b == 0) || (ps->bottom_b == 0))
		return (-2);
	ps->top_b = ps->bottom_b;
	ps->bottom_b = ps->bottom_b->prev;
	return (0);
}

int	rrr(t_stack *ps)
{
	int	command_cnt;

	if (ps == 0)
		return (-1);
	command_cnt = 0;
	if ((ps->top_a != 0) && (ps->bottom_a != 0))
	{
		ps->top_a = ps->bottom_a;
		ps->bottom_a = ps->bottom_a->prev;
		command_cnt++;
	}
	if ((ps->top_b != 0) && (ps->bottom_b != 0))
	{
		ps->top_b = ps->bottom_b;
		ps->bottom_b = ps->bottom_b->prev;
		command_cnt++;
	}
	if (command_cnt == 0)
		return (0);
	return (0);
}
