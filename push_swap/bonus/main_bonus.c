/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:54:58 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/15 16:03:11 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include "gnl/gnl.h"
#include <unistd.h>

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

void	err_exit(t_stack *ps)
{
	if (ps == 0)
		return ;
	write(2, "Error\n", ft_strlen("Error\n"));
	free_stack(ps);
	exit(-1);
}

int	main(int argc, char *argv[])
{
	t_stack				stack;
	int					splited;
	int					ret;

	if (argc < 2)
		return (0);
	ft_memset(&stack, 0, sizeof(t_stack));
	splited = 0;
	if (arg_push(&stack, argv, 1, splited) < 0)
	{
		arg_pop(&stack);
		err_exit(&stack);
	}
	if (read_operation(&stack) < 0)
		err_exit(&stack);
	ret = is_sorted_stack(&stack, stack.a_data_cnt);
	if (ret < 0)
		err_exit(&stack);
	else if (ret == 0)
		write(1, "KO\n", ft_strlen("KO\n"));
	else
		write(1, "OK\n", ft_strlen("OK\n"));
	free_stack(&stack);
	return (0);
}
