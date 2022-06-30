/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 07:54:24 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/30 22:04:17 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <unistd.h>

int	swap_list(t_list **ptop, t_list **pbottom)
{
	t_list *tmp;

	if ((ptop == 0) || (pbottom == 0))
		return (-1);
	if (*ptop == *pbottom)
		return (0);
	if ((*ptop)->next == *pbottom)
	{
		tmp = *ptop;
		*ptop = *pbottom;
		*pbottom = tmp;
		return (0);	
	}
	tmp = (*ptop)->next;
	(*ptop)->next = tmp->next;
	(*ptop)->prev = tmp;
	tmp->next->prev = *ptop;
	tmp->next = *ptop;
	(*pbottom)->next = tmp;
	tmp->prev = *pbottom;
	*ptop = tmp;
	return (0);
}

int	sa(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (swap_list(&ps->top_a, &ps->bottom_a) < 0)
		return (-1);
	if (write(1, "sa\n", ft_strlen("sa\n")) < 0)
		return (-1);
	return (0);
}

int	sb(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (swap_list(&ps->top_b, &ps->bottom_b) < 0)
		return (-1);
	if (write(1, "sa\n", ft_strlen("sb\n")) < 0)
		return (-1);
	return (0);	
}

int	ss(t_stack *ps)
{
	int	ret_sa;
	int	ret_sb;

	if (ps == 0)
		return (-1);
	ret_sa = sa(ps);
	ret_sb = sb(ps);
	if ((ret_sa < 0) && (ret_sb < 0))
		return (-1);
	if (write(1, "ss\n", ft_strlen("ss\n")) < 0)
		return (-1);
	return (0);
}

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
	if (write(1, "pa\n", ft_strlen("pa\n")) < 0)
		return (-1);
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
	if (write(1, "pb\n", ft_strlen("pb\n")) < 0)
		return (-1);
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
	if (write(1, "ra\n", ft_strlen("ra\n")) < 0)
		return (-1);
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
	if (write(1, "rb\n", ft_strlen("rb\n")) < 0)
		return (-1);
	return (0);
}

int	rr(t_stack *ps)
{
	int	ret_ra;
	int	ret_rb;

	if (ps == 0)
		return (-1);
	ret_ra = ra(ps);
	ret_rb = rb(ps);
	if ((ret_ra < 0) && (ret_rb < 0))
		return (-1);
	return (0);
}

int rra(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->top_a == 0) || (ps->bottom_b == 0))
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
	int	ret_rra;
	int	ret_rrb;

	if (ps == 0)
		return (-1);
	ret_rra = rra(ps);
	ret_rrb = rrb(ps);
	if ((ret_rra < 0) && (ret_rrb < 0))
		return (-1);
	return (0);
}
