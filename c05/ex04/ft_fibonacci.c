/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:41:23 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/22 22:52:11 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <stdlib.h>
*/
int	ft_fibonacci(int index)
{
	if (index < 0)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1)
		return (1);
	return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("argument has to be 1");
		return (0);
	}
	printf("Fibonaichi(%d) = %d\n",atoi(argv[1]),ft_fibonacci(atoi(argv[1])));
	
	return (0);
}
*/
