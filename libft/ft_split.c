/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:06:16 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/19 17:58:56 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

size_t	get_word_cnt(char const *s, char c)
{
	size_t	idx;
	size_t	word_cnt;
	int		find_delim;
	int		pre_find_delim;

	idx = 0;
	word_cnt = 0;
	find_delim = 1;
	pre_find_delim = find_delim;
	while (s[idx] != 0)
	{
		if(s[idx] == c)
			find_delim = 1;
		else
			find_delim = 0;
		if (pre_find_delim == 1 && find_delim == 0)
			word_cnt++;
		pre_find_delim = find_delim;
		idx++;
	}
	return (word_cnt);
}

int	find_start_idx(char const *s, char c, int *pstart_idx)
{
	int		idx;
	int		find_delim;
	int		prev_find_delim;

	idx = *pstart_idx;
	find_delim = 1;
	prev_find_delim = find_delim;
	while (s[idx] != 0)
	{
		if (s[idx] == c)
			find_delim = 1;
		else
			find_delim = 0;
		if (prev_find_delim == 1 && find_delim == 0)
		{
			*pstart_idx = idx;
			return (1);
		}
		prev_find_delim = find_delim;
		idx++;
	}
	return (0);
}


int	find_end_idx(char const *s, char c, int *pstart_idx, int *pend_idx)
{
	int		idx;
	int		find_delim;
	int		prev_find_delim;

	idx = *pstart_idx;
	find_delim = 1;
	prev_find_delim = find_delim;
	while (s[idx] != 0)
	{
		if (s[idx] == c)
			find_delim = 1;
		else
			find_delim = 0;
		if (prev_find_delim == 0 && find_delim == 1)
		{
			*pend_idx = idx - 1;
			return (1);
		}
		prev_find_delim = find_delim;
		idx++;
	}
	return (0);
}

char **ft_split(char const *s, char c)
{
	size_t	word_cnt;
	char 	**str;
	int		cnt;
	int		start_idx;
	int		end_idx;

	word_cnt = get_word_cnt(s, c);
	str = (char **)malloc(sizeof(char*) * (word_cnt + 1));
	if (str != NULL)
	{
		str[word_cnt] = 0;
		start_idx = 0;
		end_idx = 0;
		cnt = 0;
		while (1)
		{
			if (find_start_idx(s, c, &start_idx) != 0)
			{
				if (find_end_idx(s, c, &start_idx, &end_idx) == 0)
					end_idx = ft_strlen(s) - 1;
				str[cnt] = malloc(sizeof(char) * (end_idx - start_idx + 2));
				ft_memcpy(str, s + start_idx, end_idx - start_idx + 1);
				str[cnt++][end_idx - start_idx + 1] = 0;
				start_idx = end_idx + 1;
			}
			else
				break ;
		}
	}
	return (str);
}

int	main(int argc, char *argv[])
{
	char	**str;
	int		idx;

	if (argc != 3)
		return (0);	
	str = ft_split(argv[1],argv[2][0]);
	idx = 0;
	while (str[idx] != 0)
	{
		printf("%s\n",str[idx]);
		idx++;
	}
	//printf("%ld\n",get_word_cnt(argv[1],argv[2][0]));
	return (0);
}
