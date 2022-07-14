#include "push_swap.h"
#include <unistd.h>
#include "../libft/libft.h"

int	swap_list(t_list **ptop, t_list **pbottom)
{
	t_list	*tmp;

	if ((ptop == 0) || (pbottom == 0))
		return (-1);
	if (*ptop == *pbottom)
		return (0);
	if ((*ptop)->next == *pbottom)
	{
		tmp = *ptop;
		*ptop = *pbottom;
		*pbottom = tmp;
		return (0);
	}
	tmp = (*ptop)->next;
	(*ptop)->next = tmp->next;
	(*ptop)->prev = tmp;
	tmp->next->prev = *ptop;
	tmp->next = *ptop;
	(*pbottom)->next = tmp;
	tmp->prev = *pbottom;
	*ptop = tmp;
	return (0);
}

int	sa(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (swap_list(&ps->top_a, &ps->bottom_a) < 0)
		return (-1);
	if (write(1, "sa\n", ft_strlen("sa\n")) < 0)
		return (-1);
	return (0);
}

int	sb(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if (swap_list(&ps->top_b, &ps->bottom_b) < 0)
		return (-1);
	if (write(1, "sb\n", ft_strlen("sb\n")) < 0)
		return (-1);
	return (0);
}

int	ss(t_stack *ps)
{
	int	ret_sa;
	int	ret_sb;

	if (ps == 0)
		return (-1);
	ret_sa = swap_list(&ps->top_a, &ps->bottom_a);
	ret_sb = swap_list(&ps->top_b, &ps->bottom_b);
	if ((ret_sa < 0) && (ret_sb < 0))
		return (-1);
	if (write(1, "ss\n", ft_strlen("ss\n")) < 0)
		return (-1);
	return (0);
}
