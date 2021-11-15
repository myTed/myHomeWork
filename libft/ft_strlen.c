/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:23:48 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/10 15:29:02 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
long unsigned int	ft_strlen(const char *s)
{
	long unsigned int	idx;

	idx = 0;
	while (s[idx] != 0)
		idx++;
	return (idx);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	printf("%ld\n", ft_strlen(argv[1]));
	printf("%ld\n", strlen(argv[1]));
}
*/
