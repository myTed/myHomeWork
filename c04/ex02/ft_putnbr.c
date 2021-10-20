/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:39:22 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:12:49 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_recursive(int num)
{
	int	ch;

	if (num == 0)
	{
		return ;
	}
	print_recursive(num / 10);
	ch = num % 10 + '0';
	write(1, &ch, 1);
	return ;
}

void	ft_putnbr(int nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return ;
	}
	else if (nb < 0)
	{
		write(1, "-", 1);
		if (nb == -2147483648)
		{
			write(1, "2147483648", 10);
			return ;
		}
		else
		{
			nb = nb * -1;
		}
	}
	print_recursive(nb);
}
/*
int	main(void)
{

	ft_putnbr(2147483647);
	return (0);
}
*/
