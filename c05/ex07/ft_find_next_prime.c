/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 00:47:39 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/23 01:18:40 by kyolee           ###   ########.fr       */
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

int	ft_find_next_prime(int nb)
{
	if (nb < 1)
		return (2);
	while (!(ft_is_prime(nb)))
		nb++;
	return (nb);
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("argument has to be 2!\n");
		return (0);
	}

	printf("%d\n", ft_find_next_prime(atoi(argv[1])));
}
*/
