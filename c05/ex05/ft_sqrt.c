/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:53:15 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/22 23:49:19 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_sqrt(int nb)
{
	int	idx;

	if (nb < 0)
		return (0);
	idx = 1;
	while ((idx * idx) <= nb)
	{
		if ((idx * idx) == nb)
			return (idx);
		else
			idx++;
	}
	return (0);
}

/*
int	main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("argument has to be 1");
		return (0);
	}
	printf("%d sqrt is %d\n",atoi(argv[1]),ft_sqrt(atoi(argv[1])));
	return (0);
}
*/
