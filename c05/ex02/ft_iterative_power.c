/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:16:04 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/22 22:19:43 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_iterative_power(int nb, int power)
{
	int	num;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	num = 1;
	while (power > 0)
	{
		num = num * nb;
		power--;
	}
	return (num);
}

/*
int	main(int argc, char *argv[])
{

	if (argc != 3)
	{
		printf("argument has to be 2!");
		return (0);
	}
	printf("%d\n", ft_iterative_power(atoi(argv[1]), atoi(argv[2])));
	return (0);
}
*/
