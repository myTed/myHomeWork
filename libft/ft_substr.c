/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 23:12:05 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 19:59:47 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
/*
#include <stdio.h>
*/
static size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx] != 0)
		idx++;
	return (idx);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	str_len;
	size_t	idx;

	str_len = ft_strlen(s);
	if ((str_len <= start) || (len == 0) || (*s == 0))
		return (NULL);
	str = NULL;
	str = (char *)malloc(sizeof(char) * len);
	if (str != NULL)
	{
		idx = 0;
		while ((s[idx] != 0) && (idx < len))
		{
			str[idx] = s[start + idx];
			idx++;
		}
		str[idx] = 0;
	}
	return (str);
}

/*
int	main(int argc, char *argv[])
{
	char	*tmp;

	if (argc != 4)
		return (0);
	tmp = ft_substr(argv[1],atoi(argv[2]),atoi(argv[3]));
	if (tmp != NULL)
		printf("%s\n",tmp);
}
*/
