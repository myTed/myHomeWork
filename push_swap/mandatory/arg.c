/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:43:42 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/13 15:06:33 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	is_duplicated_arg(t_elem	num, t_stack *ps)
{
	t_list	*top;
	size_t	idx;

	top = ps->top_a;
	idx = 0;
	while (idx < ps->a_data_cnt)
	{
		if (num == top->data)
			return (1);
		top = top->next;
		idx++;
	}
	return (0);
}

int	free_split(char **str)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
	return (0);
}

static int	free_arg_check(char **split_argv)
{
	if (split_argv == 0)
		return (-1);
	if (free_split(split_argv) < 0)
		return (-1);
	return (0);
}

static int	check_push_bottm(t_stack *ps, char *str)
{
	long long int	num;
	int				overflow;

	if (ps == 0)
		return (-1);
	num = ft_atol(str, &overflow);
	if ((num > 2147483647) || (num < -2147483648))
		return (-1);
	if (is_duplicated_arg((t_elem)num, ps))
		return (-1);
	if (push_bottom(ps, num) < 0)
		return (-1);
	ps->a_data_cnt++;
	return (0);
}

int	arg_push(t_stack *ps, char *argv[], int idx, int splited)
{
	char			**split_argv;
	int				ret;

	if ((ps == 0) || (argv == 0))
		return (-1);
	while (argv[idx])
	{
		if (malloc_arg_check(argv[idx], &split_argv, &splited) < 0)
			return (-1);
		if (splited)
		{
			splited = 0;
			ret = arg_push(ps, split_argv, 0, splited);
			if (free_arg_check(split_argv) < 0)
				return (-1);
			if (ret < 0)
				return (-1);
		}
		else
			if (check_push_bottm(ps, argv[idx]) < 0)
				return (-1);
		idx++;
	}
	return (0);
}
