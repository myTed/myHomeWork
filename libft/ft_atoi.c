/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:02:40 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/16 19:59:46 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdlib.h>
#include <stdio.h>
*/
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
	if (str[tmp_idx] == '-')
		is_minus = 1;
	else
		is_minus = 0;
	tmp_idx++;
	*idx = tmp_idx;
	return (is_minus);
}

static int	get_number(const char *str, int *idx)
{
	int	tmp_idx;
	int	num;

	tmp_idx = *idx;
	num = 0;
	while (str[tmp_idx] >= '0' && str[tmp_idx] <= '9')
	{
		num = (num * 10) + (str[tmp_idx] - '0');
		tmp_idx++;
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int	idx;
	int	num;
	int	minus_signed_value;

	idx = 0;
	skip_white_space(str, &idx);
	minus_signed_value = is_minus_number(str, &idx);
	num = get_number(str, &idx);
	if (minus_signed_value)
		return (num * -1);
	else
		return (num);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	printf("std_atoi %d\n",atoi(argv[1]));
	printf("ft_atoi  %d\n",ft_atoi(argv[1]));
	return (0);
}
*/
