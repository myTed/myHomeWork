/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:51:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/21 02:45:35 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	is_duplicated(char *src)
{
	int		idx_out;
	int		idx_in;
	char	ch;

	idx_out = 0;
	while (src[idx_out] != 0)
	{
		ch = src[idx_out];
		idx_in = idx_out + 1;
		while (src[idx_in] != 0)
		{
			if (ch == src[idx_in])
				return (1);
			else
				idx_in++;
		}
		idx_out++;
	}
	return (0);
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

int	check_valid(char *base)
{
	int	len;
	int	idx;

	idx = 0;
	while (base[idx] != 0)
		idx++;
	len = idx;
	if (len <= 1)
		return (-1);
	idx = 0;
	while (base[idx] != 0)
	{
		if (base[idx] == '+' || base[idx] == '-' || base[idx] == ' '
			|| base[idx] == '\n' || base[idx] == '\t' || base[idx] == '\f'
			|| base[idx] == '\r' || base[idx] == '\v')
			return (-2);
		idx++;
	}
	if (is_duplicated(base))
		return (-3);
	return (0);
}

int	get_number(char *str, int *idx, char *base, int base_num)
{
	int		str_idx;
	int		base_idx;
	int		num;
	char	ch;

	str_idx = *idx;
	num = 0;
	base_idx = 0;
	while (str[str_idx] != 0)
	{
		ch = str[str_idx];
		base_idx = 0;
		while (base[base_idx] != 0)
		{
			if (ch == base[base_idx])
				break ;
			base_idx++;
		}
		if (base[base_idx] == 0)
			return (num);
		num = (num * base_num) + base_idx;
		str_idx++;
	}
	return (num);
}

int	ft_atoi_base(char *str, char *base)
{
	int	num;
	int	minus_signed_value;
	int	idx;
	int	base_num;

	idx = 0;
	num = 0;
	base_num = 0;
	if (check_valid(base) < 0)
		return (0);
	while (str[idx] == ' ' || str[idx] == '\n' || str[idx] == '\t'
		|| str[idx] == '\f' || str[idx] == '\r' || str[idx] == '\v')
		idx++;
	minus_signed_value = is_minus_number(str, &idx);
	while (base[base_num] != 0)
		base_num++;
	num = get_number(str, &idx, base, base_num);
	if (minus_signed_value)
		return (num * -1);
	else
		return (num);
}
/*
int	main(void)
{
	printf("%s\n","---+--+1234ab567");
	printf("%d\n",ft_atoi_base("DC542","0123456789ABCDEF"));	
	return (0);
}
*/
