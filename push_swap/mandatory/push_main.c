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
	/*	
	print_stack(stack.top_a, stack.bottom_a);
	printf("\n");
	print_stack(stack.top_b, stack.bottom_b);
	printf("\n");
	*/	
	sort_bigger(&stack, idx - 1);
	/*	
	print_stack(stack.top_a, stack.bottom_a);
	printf("\n");
	*/
	/*
	char buff[128];	
	while (1)
	{
		read(0, buff, 100);
		if (!ft_strncmp(buff, "sa\n", ft_strlen("sa\n")))
		{
			printf("%s", buff);
			sa(&stack);
		}			
		if (!ft_strncmp(buff, "sb\n", ft_strlen("sb\n")))
		{
			printf("%s", buff);
			sb(&stack);
		}
		if (!ft_strncmp(buff, "ss\n", ft_strlen("ss\n")))
		{
			printf("%s", buff);
			ss(&stack);
		}
		if (!ft_strncmp(buff, "pa\n", ft_strlen("pa\n")))
		{	
			printf("%s", buff);
			pa(&stack);
		}
		if (!ft_strncmp(buff, "pb\n", ft_strlen("pb\n")))
		{
			printf("%s", buff);
			pb(&stack);
		}
		if (!ft_strncmp(buff, "ra\n", ft_strlen("ra\n")))
		{
			printf("%s", buff);
			ra(&stack);
		}
		if (!ft_strncmp(buff, "rb\n", ft_strlen("rb\n")))
		{
			printf("%s", buff);
			rb(&stack);
		}
		if (!ft_strncmp(buff, "rr\n", ft_strlen("rr\n")))
		{
			printf("%s", buff);
			rr(&stack);
		}
		if (!ft_strncmp(buff, "rra\n", ft_strlen("rra\n")))
		{
			printf("%s", buff);
			rra(&stack);
		}
		if (!ft_strncmp(buff, "rrb\n", ft_strlen("rrb\n")))
		{
			printf("%s", buff);
			rrb(&stack);
		}
		if (!ft_strncmp(buff, "rrr\n", ft_strlen("rrr\n")))
		{
			printf("%s", buff);
			rrr(&stack);
		}
		printf("A: ");
		print_stack(stack.top_a, stack.bottom_a);
		printf("\n");
		printf("B: ");
		print_stack(stack.top_b, stack.bottom_b);
		printf("\n");
	}
	*/
	/*
	idx = 1;
	while (argv[idx])
	{
		push(&stack, atoi(argv[idx]), &stack.top_a, &stack.bottom_a); 
		idx++;
		print_stack(stack.top_a, stack.bottom_a);
		printf("\n");
	}
	*/
	return (0);
}

