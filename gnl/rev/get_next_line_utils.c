/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:00:16 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/25 16:21:39 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
/*
t_list	*ft_lstnew(void **content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
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

void	ft_lstclear(t_list **lst)
{
	t_list	*cur_pos;
	t_list	*del_pos;

	if (lst == 0)
		return ;
	cur_pos = *lst;
	while (cur_pos != 0)
	{
		del_pos = cur_pos;
		cur_pos = cur_pos->next;
		//free(del_pos->content);
		free(del_pos);
	}
	*lst = 0;
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
int	get_pos_newline_in_buffer(
	char *buff,
	size_t size,
	int *is_found_newline
){
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		if (buff[idx] == '\n')
		{
			*is_found_newline = 1;
			return (idx);
		}
		idx++;
	}
	*is_found_newline = 0;
	return (0);
}
*/
