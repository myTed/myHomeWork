/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:00:16 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/12 00:33:21 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>

t_list	*ft_lstnew(int fd, void *str, size_t str_len)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->left = str;
	new->left_len = str_len;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		end = *lst;
		while (end->next != NULL)
			end = end->next;
		end->next = new;
	}
}

void	ft_lstdel(t_list **lst, int fd)
{
	t_list	*cur;
	t_list	*prev;

	cur = *lst;
	prev = cur;
	if (lst == 0)
		return ;
	while (cur != 0)
	{
		if (cur->fd == fd)
		{	
			if (prev == cur)
				*lst = cur->next;
			else
				prev->next = cur->next;
			free(cur->left);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

size_t	ft_strlen(void *src)
{
	size_t	idx;

	idx = 0;
	if (src == 0)
		return (0);
	while (((char *)src)[idx] != 0)
		idx++;
	return (idx);
}

char	*ft_strjoin(
		char const *s1,
		char const *s2,
		size_t s1_len,
		size_t s2_len
){
	char	*str;
	size_t	idx;

	if ((s1 == 0 && s2 == 0))
		return (NULL);
	if (s1_len == 0 && s2_len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == 0)
		return (NULL);
	idx = 0;
	while (s1 && (idx < s1_len))
	{
		str[idx] = s1[idx];
		idx++;
	}
	idx = 0;
	while (s2 && (idx < s2_len))
	{
		str[idx + s1_len] = s2[idx];
		idx++;
	}
	str[s1_len + s2_len] = 0;
	return (str);
}
