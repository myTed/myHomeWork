/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:00:16 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/06 23:49:53 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

char	*ft_strdup(const char *s, size_t size)
{
	char	*str;
	size_t	idx;

	if (s == 0 || size == 0)
		return (0);
	str = NULL;
	str = malloc(size + 1);
	idx = 0;
	if (str != NULL)
	{
		while (idx < size)
		{
			str[idx] = s[idx];
			idx++;
		}
		str[idx] = 0;
	}
	return (str);
}

char	*ft_strjoin(
	char const *s1,
	char const *s2,
	size_t s1_len,
	size_t s2_len
){
	char	*str;
	size_t	idx;

	if (s1 == 0 && s2 == 0)
		return (NULL);
	else if ((s1 != 0) && (s2 == 0))
		return (ft_strdup(s1, s1_len));
	else if ((s2 != 0) && (s1 == 0))
		return (ft_strdup(s2, s2_len));
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == 0)
		return (0);
	idx = 0;
	while (idx < s1_len + s2_len)
	{
		if (idx < s1_len)
			str[idx] = s1[idx];
		else
			str[idx] = s2[idx - s1_len];
		idx++;
	}
	str[s1_len + s2_len] = 0;
	return (str);
}

int	is_found_enter(char *s, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		if (s[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}

int	expand_buff(
	char **buff,
	size_t read_cnt,
	size_t cur_len,
	size_t plus_len
){
	char	*new;
	size_t	idx;

	new = malloc(sizeof(char) * (cur_len + plus_len));
	if (new == 0)
		return (0);
	idx = 0;
	while (idx < read_cnt)
	{
		new[idx] = (*buff)[idx];
		idx++;
	}
	free(*buff);
	*buff = new;
	return (1);
}

int	init_read_info_arr(t_read *pread_info)
{
	t_fd_arr	*tmp;

	tmp = malloc(sizeof(t_fd_arr) * FD_BUF_MAX);
	if (tmp == 0)
		return (-1);
	pread_info->parr = tmp;
	pread_info->arr_max = FD_BUF_MAX;
	pread_info->arr_cur_len = 0;
	return (0);
}
