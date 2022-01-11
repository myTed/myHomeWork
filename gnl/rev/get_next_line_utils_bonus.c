/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:00:16 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/11 17:40:58 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
/*
t_list	*ft_lstnew(void *content, size_t len, int is_newline)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->len = len;
	new->is_newline = is_newline;
	new->ready_to_free = 0;
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

void	delete_list(t_list **pplist, int error)
{
	t_list	*del;

	if (error == MEM_ALLOC_ERROR)
	{
		while ((*pplist != NULL))
		{
			del = *pplist;
			*pplist = (*pplist)->next;
			free(del->content);
			free(del);
		}
	}
	else
	{
		while ((*pplist != NULL) && ((*pplist)->ready_to_free))
		{
			del = *pplist;
			*pplist = (*pplist)->next;
			free(del);
		}
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		if ((dest == 0) && (src == 0))
			return (0);
		*((unsigned char *)dest + idx) = *((const unsigned char *)src + idx);
		idx++;
	}
	return (dest);
}

int	is_found_newline(char *buff, ssize_t size)
{
	ssize_t	idx;

	idx = 0;
	while (idx < size)
	{
		if (buff[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}
*/
