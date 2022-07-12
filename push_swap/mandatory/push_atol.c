/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_atol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:02:40 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/11 22:18:48 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	skip_white_space(const char *str, int *idx)
{
	int	tmp_idx;

	tmp_idx = *idx;
	while (str[tmp_idx] == '\t' || str[tmp_idx] == '\n'\
			|| str[tmp_idx] == '\v' || str[tmp_idx] == '\f'\
			|| str[tmp_idx] == ' ' || str[tmp_idx] == '\r')
	{
		tmp_idx++;
	}
	*idx = tmp_idx;
}

static int	is_minus_number(const char *str, int *idx)
{
	int	tmp_idx;
	int	is_minus;

	tmp_idx = *idx;
	is_minus = 0;
	if ((str[tmp_idx] == '-') || (str[tmp_idx] == '+'))
	{
		if (str[tmp_idx] == '-')
			is_minus = 1;
		tmp_idx++;
	}
	*idx = tmp_idx;
	return (is_minus);
}

static long long int get_number(const char *str, int *idx, int *overflow)
{
	int				tmp_idx;
	long long int	num;
	long long int	tmp_num;

	tmp_idx = *idx;
	num = 0;
	while (str[tmp_idx] >= '0' && str[tmp_idx] <= '9')
	{
		tmp_num = (num * 10) + (str[tmp_idx] - '0');
		tmp_idx++;
		if (tmp_num < num)
		{
			*overflow = 1;
		}
		num = tmp_num;
	}
	return (num);
}

long long int ft_atol(const char *str, int *poverflow)
{
	int				idx;
	long long int	num;
	int				minus_signed_value;

	idx = 0;
	*poverflow = 0;
	skip_white_space(str, &idx);
	minus_signed_value = is_minus_number(str, &idx);
	num = get_number(str, &idx, poverflow);
	if (*poverflow)
	{
		if (minus_signed_value)
			return (0);
		else
			return (-1);
	}
	else
	{
		if (minus_signed_value)
			return (num * -1);
		else
			return (num);
	}
}
