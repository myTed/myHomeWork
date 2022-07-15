/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_pop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:12:55 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:12:56 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include <unistd.h>
#include "../libft/libft.h"

int	pa(t_stack *ps)
{
	t_elem	data;

	if (ps == 0)
		return (-1);
	if (pop(ps, &ps->top_b, &ps->bottom_b, &data) < 0)
		return (-1);
	ps->b_data_cnt--;
	if (push(ps, data, &ps->top_a, &ps->bottom_a) < 0)
		return (-1);
	ps->a_data_cnt++;
	return (0);
}

int	pb(t_stack *ps)
{
	t_elem	data;

	if (ps == 0)
		return (-1);
	if (pop(ps, &ps->top_a, &ps->bottom_a, &data) < 0)
		return (-1);
	ps->a_data_cnt--;
	if (push(ps, data, &ps->top_b, &ps->bottom_b) < 0)
		return (-1);
	ps->b_data_cnt++;
	return (0);
}

int	ra(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->bottom_a == 0) || (ps->top_a == 0))
		return (-2);
	ps->bottom_a = ps->top_a;
	ps->top_a = ps->top_a->next;
	return (0);
}

int	rb(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->bottom_b == 0) || (ps->top_b == 0))
		return (-2);
	ps->bottom_b = ps->top_b;
	ps->top_b = ps->top_b->next;
	return (0);
}
