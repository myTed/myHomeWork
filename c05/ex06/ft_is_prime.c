/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:51:05 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/23 00:46:38 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_is_prime(int nb)
{
	int	idx;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (0);
	idx = 2;
	while (idx < nb)
	{
		if (nb % idx == 0)
			return (0);
		idx++;
	}
	return (1);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("argument has to be 2!\n");
		return (0);
	}
	
	printf("ft_is_prime(%d) is %s\n"\
	,atoi(argv[1]),ft_is_prime(atoi(argv[1]))? "prime!" : "no prime!");
}
*/
