/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:07:43 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/28 20:44:07 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <stdio.h>
*/
void	ft_lstadd_back(t_lib_list **lst, t_lib_list *new)
{
	t_lib_list	*end;

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

/*
int	main(void)
{
	t_list	*start;
	start = ft_lstnew("aaa");
	ft_lstadd_front(&start, ft_lstnew("bbb"));

	ft_lstadd_back(&start, ft_lstnew("ccc"));

	while (start != NULL)
	{
		printf("%s\n", start->content);
		start = start->next;
	}
	return (0);
}
*/
