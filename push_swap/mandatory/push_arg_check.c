/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_check_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:57:31 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/13 15:18:12 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include "../libft/libft.h"

static int	is_empty_str(char *str)
{
	if (str == 0)
		return (-1);
	return (!str[0]);
}

static int	is_char_str(char *str)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	while (str[idx])
	{
		if (ft_isalpha(str[idx]))
			return (1);
		idx++;
	}
	return (0);
}

static int	is_over_range_int(char **str)
{
	int			idx;
	long long	num;
	int			overflow;

	idx = 0;
	overflow = 0;
	while (str[idx])
	{		
		num = ft_atol(str[idx], &overflow);
		if (overflow)
			return (-1);
		if ((num > 2147483647) || (num < -2147484648))
			return (-1);
		idx++;
	}
	return (0);
}

static int	get_space_cnt(char *str, size_t	*pspace_cnt)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	*pspace_cnt = 0;
	while (str[idx])
	{
		if (str[idx] == ' ')
			(*pspace_cnt)++;
		idx++;
	}
	return (0);
}

int	malloc_arg_check(char *str, char ***psplit_argv, int *psplited)
{
	size_t	len;
	size_t	space_cnt;

	if (is_empty_str(str) == 1)
		return (-1);
	if (is_char_str(str) == 1)
		return (-1);
	len = ft_strlen(str);
	if (get_space_cnt(str, &space_cnt) < 0)
		return (-1);
	if (len == space_cnt)
		return (-1);
	if (space_cnt)
	{
		*psplit_argv = ft_split(str, ' ');
		if (*psplit_argv == 0)
			return (-1);
		if (is_over_range_int(*psplit_argv))
		{
			free_split(*psplit_argv);
			return (-1);
		}
		*psplited = 1;
	}
	return (0);
}
