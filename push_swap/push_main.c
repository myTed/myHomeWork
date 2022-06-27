#include <stdio.h>
#include "push_swap.h"
#include <stdlib.h>

int	init_stack(t_stack *s)
{
	if (s == 0)
		return (-1);
	s->top_a = 0;
	s->top_b = 0;
	s->bottom_a = 0;
	s->bottom_b = 0;
	return (0);
}

int	arg_push(t_stack *s, t_elem elem, t_list **ptop, t_list **pbottom)
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
		*pbottom = pnew;
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

int	pop(t_stack *s, t_list **ptop, t_list **pbottom)
{
	t_list *del;

	if ((s == 0) || (ptop == 0) || (pbottom == 0))
		return (-1);
	del = *ptop;
	if (*ptop == *pbottom)
	{
		free(del);
		*ptop = 0;
		*pbottom = 0;
	}
	else
	{
		*ptop = (*ptop)->next;
		(*pbottom)->next = *ptop;
		(*ptop)->prev = *pbottom;
		free(del);
	}
	return (0);
}

int	free_stack(t_stack *s)
{
	if (s == 0)
		return (-1);
	while (s->top_a)
		pop(s, &s->top_a, &s->bottom_a);
	while (s->top_b)
		pop(s, &s->top_b, &s->bottom_b);
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




int	main(int argc, char *argv[])
{
	t_stack stack;
	int		idx;
	
	if (argc == 1)
		return (-1);
	init_stack(&stack);
	idx = 1;
	while (argv[idx])
	{
		arg_push(&stack, atoi(argv[idx]), &stack.top_a, &stack.bottom_a); 
		idx++;
	}
	
	idx = 0;
	while (idx < 5)
	{
		print_stack(stack.top_a, stack.bottom_a);
		printf("\n");
		pop(&stack, &stack.top_a, &stack.bottom_a);
		idx++;
	}

	idx = 1;
	while (argv[idx])
	{
		push(&stack, atoi(argv[idx]), &stack.top_a, &stack.bottom_a); 
		idx++;
		print_stack(stack.top_a, stack.bottom_a);
		printf("\n");
	}

	return (0);
}

