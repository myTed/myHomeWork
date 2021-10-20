/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 01:07:14 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:25:34 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_strlen(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		idx++;
	}
	return (idx);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	idx;
	int	fnd_idx;
	int	len;

	len = ft_strlen(to_find);
	idx = 0;
	fnd_idx = 0;
	if (to_find[idx] == 0)
		return (str);
	while (str[idx] != 0)
	{
		if (to_find[fnd_idx] == str[idx])
		{
			fnd_idx++;
			if (fnd_idx == len)
				return (&str[idx - fnd_idx + 1]);
		}
		else
			fnd_idx = 0;
		idx++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *str = "1232255";
	char *src = "224";
	char *find;

	find = NULL;
	find = ft_strstr(str, src);
	if (find != NULL)
	{
		printf("ft_str: %s\n",find);
	}
	else
	{
		printf("not found\n");
	}

	printf("\n");
	printf("strstr: %s\n",strstr(str, src));

	return (0);
}
*/
