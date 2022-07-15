/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:19:56 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/15 19:20:46 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include "../libft/libft.h"
#include "gnl/gnl.h"
#include <stdlib.h>

int	cmd_operation_rotate(char *cmd, t_stack *ps)
{
	if ((cmd == 0) || (ps == 0))
		return (-1);
	if (!ft_strncmp(cmd, "ra\n", 3))
		ra(ps);
	else if (!ft_strncmp(cmd, "rb\n", 3))
		rb(ps);
	else if (!ft_strncmp(cmd, "rr\n", 3))
		rr(ps);
	else if (!ft_strncmp(cmd, "rra\n", 4))
		rra(ps);
	else if (!ft_strncmp(cmd, "rrb\n", 4))
		rrb(ps);
	else if (!ft_strncmp(cmd, "rrr\n", 4))
		rrr(ps);
	else
		return (-1);
	return (0);
}

int	cmd_operation(char *cmd, t_stack *ps)
{
	if (cmd == 0 || ps == 0)
		return (-1);
	if (!ft_strncmp(cmd, "sa\n", 3))
		sa(ps);
	else if (!ft_strncmp(cmd, "sb\n", 3))
		sb(ps);
	else if (!ft_strncmp(cmd, "sa\n", 3))
		ss(ps);
	else if (!ft_strncmp(cmd, "pa\n", 3))
		pa(ps);
	else if (!ft_strncmp(cmd, "pb\n", 3))
		pb(ps);
	else
		return (cmd_operation_rotate(cmd, ps));
	return (0);
}

int	read_operation(t_stack *ps)
{
	char	*cmd;

	while (1)
	{
		cmd = get_next_line(0);
		if (cmd == 0)
			break ;
		if (cmd_operation(cmd, ps) < 0)
			return (-1);
		free(cmd);
	}
	return (0);
}

int	is_already_ordered_stack_a(t_stack *ps, int n)
{
	int		idx;
	t_list	*ptmp_top;

	ptmp_top = ps->top_a;
	idx = 0;
	while (idx < n - 1)
	{
		if (ptmp_top->data > ptmp_top->next->data)
			return (0);
		idx++;
		ptmp_top = ptmp_top->next;
	}
	return (1);
}

int	is_sorted_stack(t_stack *ps, size_t unordered_cnt)
{
	if (ps == 0)
		return (-1);
	if (ps->b_data_cnt != 0)
		return (0);
	if (ps->a_data_cnt != unordered_cnt)
		return (0);
	return (is_already_ordered_stack_a(ps, ps->a_data_cnt));
}
