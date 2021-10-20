/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 00:02:36 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:17:30 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while (s1[idx] != 0 || s2[idx] != 0)
	{
		if (s1[idx] != s2[idx])
		{
			return (s1[idx] - s2[idx]);
		}
		idx++;
	}
	return (0);
}
/*
int	main(void)
{
	char *str1 = "aaaaa";
	char *str2 = "aaaaa";

	printf("%d\n", ft_strcmp(str1, str2));
	printf("%d\n", strcmp(str1, str2));
}
*/
