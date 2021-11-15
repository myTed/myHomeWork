/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:47:49 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/12 13:51:29 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <bsd/string.h>
#include <string.h>
*/
static size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		idx++;
	}
	return (idx);
}

static size_t	check_equal(const char *big, const char *little, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (big[idx] != little[idx])
			return (0);
		idx++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	idx;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little[0] == 0)
		return ((char *)big);
	idx = 0;
	while ((big[idx] != 0) && (idx < len))
	{
		if (check_equal(&big[idx], little, little_len) != 0)
			return ((char *)&big[idx]);
		idx++;
	}
	return (0);
}
/*
int	main(void)
{
	const char 	*str = "1232255";
	const char 	*src = "255";
	char 	*find;

	find = NULL;
	find = ft_strnstr(str, src, 7);
	if (find != NULL)
	{
		printf("ft_str: %s\n",find);
	}
	else
	{
		printf("not found\n");
	}
	
	printf("\n");
	printf("strstr: %s\n",strnstr(str, src, strlen(str)));
	
	return (0);
}
*/
