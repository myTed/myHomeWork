/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:30:47 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/22 21:07:21 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_iterative_factorial(int nb)
{
	int	num;

	num = 1;
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	while (nb != 0)
	{
		num = num * nb;
		nb--;
	}
	return (num);
}

/*
int	main(int argc, char *argv[])
{

	if (argc != 2)
	{
		return (0);	
	}
	printf("%d\n", ft_iterative_factorial(atoi(argv[1])));

	return (0);
}
*/
