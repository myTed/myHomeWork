#include <stdio.h>
#include "push_swap.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>

int	init_stack(t_stack *s)
{
	if (s == 0)
		return (-1);
	ft_memset(s, 0, sizeof(t_stack));
	return (0);
}

int	push_bottom(t_stack *ps, t_elem elem)
{
	t_list *pnew;

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
	t_list *pnew;

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
	t_list *del;

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

int	free_stack(t_stack *s)
{
	t_elem data;

	if (s == 0)
		return (-1);
	while (s->top_a)
		pop(s, &s->top_a, &s->bottom_a, &data);
	while (s->top_b)
		pop(s, &s->top_b, &s->bottom_b, &data);
	return (0);
}

int	print_stack(t_list *ptop, t_list *pbottom)
{
	t_list *ptmp;
	
	if ((ptop == 0) || (pbottom == 0))
		return (-1);
	ptmp = ptop;
	do
	{
		printf("%d ", ptmp->data);
		ptmp = ptmp->next;
	} while (ptmp != ptop);
	return (0);
}


t_elem	quick_select(t_select_stack *psel, t_list *top, size_t order, size_t size)
{
	t_list *tmp_top;
	t_elem	pivot;
	size_t	idx;
	size_t	big_cnt;
	size_t	medium_cnt;
	size_t	small_cnt;

	tmp_top = top;
	pivot = tmp_top->next->data;
	idx = 0;
	big_cnt = 0;
	medium_cnt = 0;
	small_cnt = 0;
	while (idx < size)
	{
		if (tmp_top->data < pivot)
		{
			push(&(psel->small), tmp_top->data, &(psel->small.top_a), &(psel->small.bottom_a));
			small_cnt++;
		}
		else if (tmp_top->data > pivot)
		{
			push(&(psel->big), tmp_top->data, &(psel->big.top_a), &(psel->big.bottom_a));
			big_cnt++;
		}
		else
		{
			push(&(psel->medium), tmp_top->data, &(psel->medium.top_a), &(psel->medium.bottom_a));
			medium_cnt++;
		}
		idx++;
		tmp_top = tmp_top->next;
	}
	if (small_cnt >= order)
		return quick_select(psel, psel->small.top_a, order, small_cnt);
	else if (small_cnt + medium_cnt < order)
		return quick_select(psel, psel->big.top_a, order - small_cnt - medium_cnt, big_cnt);
	else
		return (pivot);
}

int	init_select_stack(t_select_stack *ps)
{
	if (ps == 0)
		return (-1);
	ft_memset(&ps->big, 0, sizeof(t_stack));
	ft_memset(&ps->medium, 0, sizeof(t_stack));
	ft_memset(&ps->small, 0, sizeof(t_stack));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_stack 		stack;
	t_select_stack	s_stack;

	if (argc < 2)
		return (0);
	init_stack(&stack);
	init_select_stack(&s_stack);
	if (arg_push(&stack, argv, 1) < 0)
	{
		write(2, "Error\n", ft_strlen("Error\n"));
		return (-1);
	}
	quick_sort_a(&s_stack, &stack, stack.a_data_cnt, 1);
	//print_stack(stack.top_a, stack.bottom_a);	
	return (0);
}

