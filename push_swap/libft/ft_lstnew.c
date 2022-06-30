/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:12:48 by kyolee            #+#    #+#             */
/*   Updated: 2022/06/28 20:46:19 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_lib_list	*ft_lstnew(void *content)
{
	t_lib_list	*new;

	new = (t_lib_list *)malloc(sizeof(t_lib_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*
int	main(void)
{
	t_list *start;

	start = ft_lstnew("aaaa");
	printf("%s\n",start->content);
}
*/
