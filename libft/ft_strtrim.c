/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:31:37 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 19:59:36 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
/*
#include <stdio.h>
*/
static size_t	ft_strlen(const char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] != 0)
		idx++;
	return (idx);
}

static int	is_duplicated(const char ch, char const *set)
{
	size_t	idx;

	idx = 0;
	while (set[idx] != 0)
	{
		if (ch == set[idx])
			return (1);
		idx++;
	}
	return (0);
}

static int	find_start_idx(char const *str, char const *set, int str_len)
{
	int	idx;

	idx = 0;
	while (idx < str_len)
	{
		if (is_duplicated(str[idx], set))
			idx++;
		else
			break ;	
	}
	return (idx);
}

static int	find_end_idx(char const *str, char const *set, int str_len)
{
	int	idx;
	
	idx = 0;
	while (idx < str_len)
	{
		if (is_duplicated(str[str_len - 1 - idx], set))
		{
			idx++;
		}
		else
			break ;
	}
	return (str_len - 1 - idx);
}


char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start_idx;
	int		end_idx;
	int		idx;
	char	*str;

	len = ft_strlen(s1);
	start_idx = find_start_idx(s1, set, len);
	end_idx = find_end_idx(s1, set, len);
	if (start_idx > len || end_idx < 0)
		return malloc(0);
	str = NULL;
	str = malloc(sizeof(char) * (end_idx - start_idx + 1));
	if (str != NULL)
	{
		idx = 0;
		while (idx < end_idx - start_idx + 1)
		{
			str[idx] = s1[start_idx + idx];
			idx++;
		}
	}
	return (str);
}


/*
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
*/
/*
int	main(void)
{
	char	*tmp;
	if ((tmp = ft_strtrim("asdf",0)) != NULL)
	{
		printf("%s\n", tmp);
	}
	return (0);
}
*/
