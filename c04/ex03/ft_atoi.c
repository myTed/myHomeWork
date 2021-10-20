/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:51:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/21 01:01:20 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	skip_white_space(char *str, int *idx)
{
	int	tmp_idx;

	tmp_idx = *idx;
	while (str[tmp_idx] == ' ' || str[tmp_idx] == '\n'\
		|| str[tmp_idx] == '\t' || str[tmp_idx] == '\f'\
		|| str[tmp_idx] == '\r' || str[tmp_idx] == '\v')
	{
		tmp_idx++;
	}
	*idx = tmp_idx;
}

int	is_minus_number(char *str, int *idx)
{
	int	tmp_idx;
	int	minus_cnt;

	tmp_idx = *idx;
	minus_cnt = 0;
	while (str[tmp_idx] == '+' || str[tmp_idx] == '-')
	{
		if (str[tmp_idx] == '-')
		{
			minus_cnt++;
		}
		tmp_idx++;
	}
	*idx = tmp_idx;
	return (minus_cnt % 2);
}

int	get_number(char *str, int *idx)
{
	int	tmp_idx;
	int	num;

	tmp_idx = *idx;
	num = 0;
	while (str[tmp_idx] >= '0' && str[tmp_idx] <= '9')
	{
		num = num * 10 + (str[tmp_idx] - '0');
		tmp_idx++;
	}
	*idx = tmp_idx;
	return (num);
}

int	ft_atoi(char *str)
{
	int	num;
	int	minus_signed_value;
	int	idx;

	idx = 0;
	num = 0;
	skip_white_space(str, &idx);
	minus_signed_value = is_minus_number(str, &idx);
	num = get_number(str, &idx);
	if (minus_signed_value)
		return (num * -1);
	else
		return (num);
}

/*
int	main(void)
{
	printf("%s\n"," ---+--+1234ab567");
	printf("ft_atoi: %d\n", ft_atoi("  -a12a1234ab567"));
	printf("atoi   : %d\n", atoi("  -a12a1234ab567"));
}
*/
