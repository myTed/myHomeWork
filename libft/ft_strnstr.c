/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:47:49 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 21:55:49 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>
#include <string.h>

#include <stddef.h>

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

static size_t	check_equal(const char *big, const char *little, size_t search_len, size_t little_len)
{
	size_t	idx;

	idx = 0;
	while (idx < search_len)
	{
		if (big[idx] != little[idx])
			return (0);
		idx++;
	}
	if (idx == little_len)
		return (1);
	else
		return (0);
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
		if (check_equal(&big[idx], little, len - 1 - idx, little_len) != 0)
			return ((char *)&big[idx]);
		idx++;
	}
	return (0);
}

int	main(void)
{
	const char 	*str = "lorem ipsum dolor sit amet";
	const char 	*src = "dolor";
	char 	*find;

	find = NULL;
	find = ft_strnstr(str, src, 15);
	if (find != NULL)
	{
		printf("ft_str: %s\n",find);
	}
	else
	{
		printf("not found\n");
	}
	
	printf("\n");
	printf("strstr: %s\n",strnstr(str, src, 15));
	
	return (0);
}

