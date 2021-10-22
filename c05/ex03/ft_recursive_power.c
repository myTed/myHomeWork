/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:36:58 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/22 22:37:02 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("argument has to be 3!");
		return (0);
	}

	printf("%d\n",ft_recursive_power(atoi(argv[1]),atoi(argv[2])));
	
	return (0);
}
*/
