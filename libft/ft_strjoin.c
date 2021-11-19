/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 23:54:05 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 19:57:55 by kyolee           ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		idx;

	if ((*s1 == 0) && (*s2 == 0))
		return (NULL);
	str = NULL;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str != NULL)
	{
		idx = 0;
		while (s1[idx] != 0)
		{
			str[idx] = s1[idx];
			idx++;
		}
		idx = 0;
		while (s2[idx] != 0)
		{
			str[ft_strlen(s1) + idx] = s2[idx];
			idx++;
		}
		str[ft_strlen(s1) + ft_strlen(s2)] = 0;
	}
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	char	*tmp;
	if (argc != 3)
		return (0);
	tmp = ft_strjoin(argv[1],argv[2]);
	if (tmp != NULL)
		printf("%s\n",tmp);
}
*/
