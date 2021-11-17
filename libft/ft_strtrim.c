/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:31:37 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 03:03:42 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

static int	is_duplicated(char ch, char const *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if (ch == str[idx])
			return (1);
		idx++;
	}
	return (0);
}

char	*str_cpy_without_duplicated(char *dest, char const *src, char const *set)
{
	size_t	idx;
	size_t	dest_idx;

	idx = 0;
	dest_idx = 0;
	while (src[idx] != 0)
	{
		if (!is_duplicated(src[idx], set))
		{
			dest[dest_idx] = src[idx];
			dest_idx++;
		}
		idx++;
	}
	dest[dest_idx] = 0;
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		str_len;
	char		*str;
	size_t		idx;

	str_len = 0;
	idx = 0;
	while (s1[idx] != 0)
	{
		if (!is_duplicated(s1[idx], set))
			str_len++;
		idx++;
	}
	str = NULL;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str != NULL)
		str = str_cpy_without_duplicated(str, s1, set);
	return (str);
}



int	main(int argc, char *argv[])
{
	char	*tmp;
	if (argc != 3)
		return (0);
	tmp = NULL;
	if ((tmp = ft_strtrim(argv[1],argv[2])) != NULL)
	{
		printf("%s\n",tmp);
	}
	return (0);
}
