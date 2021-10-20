/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:03:25 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:15:33 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

int	ft_strlen(char *src)
{
	int	idx;

	idx = 0;
	while (src[idx] != 0)
		idx++;
	return (idx);
}

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

int	check_valid(char *base)
{
	int	len;
	int	idx;

	len = ft_strlen(base);
	if (len <= 1)
		return (-1);
	idx = 0;
	while (base[idx] != 0)
	{
		if (base[idx] == '+' || base[idx] == '-')
			return (-2);
		idx++;
	}
	if (is_duplicated(base))
		return (-3);
	return (0);
}

void	recursive_print(unsigned int num, int base_num, char *str_base)
{
	if (num == 0)
		return ;
	recursive_print(num / base_num, base_num, str_base);
	write(1, &str_base[num % base_num], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	base_num;

	if (check_valid(base) < 0)
		return ;
	base_num = ft_strlen(base);
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return ;
	}
	recursive_print(nbr, base_num, base);
}

/*
int	main(void)
{
	ft_putnbr_base(-1,"0123456789ABCDEF");
}
*/
