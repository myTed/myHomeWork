/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:13:06 by kyolee            #+#    #+#             */
/*   Updated: 2022/07/14 21:13:26 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include <stdlib.h>

int	push_bottom(t_stack *ps, t_elem elem)
{
	t_list	*pnew;

	if (ps == 0)
		return (-1);
	pnew = malloc(sizeof(t_list));
	if (pnew == 0)
		return (-1);
	pnew->data = elem;
	if (ps->top_a == 0)
	{
		pnew->prev = pnew;
		pnew->next = pnew;
		ps->top_a = pnew;
		ps->bottom_a = pnew;
	}
	else
	{
		ps->bottom_a->next = pnew;
		ps->top_a->prev = pnew;
		pnew->prev = ps->bottom_a;
		pnew->next = ps->top_a;
		ps->bottom_a = pnew;
	}
	return (0);
}

int	push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom)
{
	t_list	*pnew;

	if (s == 0)
		return (-1);
	pnew = malloc(sizeof(t_list));
	if (pnew == 0)
		return (-1);
	pnew->data = elem;
	if (*ptop == 0)
	{
		pnew->prev = pnew;
		pnew->next = pnew;
		*ptop = pnew;
		*pbottom = pnew;
	}
	else
	{
		(*pbottom)->next = pnew;
		(*ptop)->prev = pnew;
		pnew->prev = *pbottom;
		pnew->next = *ptop;
		*ptop = pnew;
	}
	return (0);
}

int	pop(t_stack *s, t_list **ptop, t_list **pbottom, t_elem *pdata)
{
	t_list	*del;

	if ((s == 0) || (ptop == 0) || (pbottom == 0))
		return (-1);
	del = *ptop;
	if ((*ptop == 0) && (*pbottom == 0))
		return (-2);
	if (*ptop == *pbottom)
	{
		*pdata = (*ptop)->data;
		free(del);
		*ptop = 0;
		*pbottom = 0;
	}
	else
	{
		*pdata = (*ptop)->data;
		*ptop = (*ptop)->next;
		(*pbottom)->next = *ptop;
		(*ptop)->prev = *pbottom;
		free(del);
	}
	return (0);
}
