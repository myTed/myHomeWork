#include "push_swap.h"
#include <unistd.h>
#include "../libft/libft.h"

int	pa(t_stack *ps)
{
	t_elem	data;

	if (ps == 0)
		return (-1);
	if (pop(ps, &ps->top_b, &ps->bottom_b, &data) < 0)
		return (-1);
	ps->b_data_cnt--;
	if (push(ps, data, &ps->top_a, &ps->bottom_a) < 0)
		return (-1);
	ps->a_data_cnt++;
	if (write(1, "pa\n", ft_strlen("pa\n")) < 0)
		return (-1);
	return (0);
}

int	pb(t_stack *ps)
{
	t_elem	data;

	if (ps == 0)
		return (-1);
	if (pop(ps, &ps->top_a, &ps->bottom_a, &data) < 0)
		return (-1);
	ps->a_data_cnt--;
	if (push(ps, data, &ps->top_b, &ps->bottom_b) < 0)
		return (-1);
	ps->b_data_cnt++;
	if (write(1, "pb\n", ft_strlen("pb\n")) < 0)
		return (-1);
	return (0);
}

int	ra(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->bottom_a == 0) || (ps->top_a == 0))
		return (-2);
	ps->bottom_a = ps->top_a;
	ps->top_a = ps->top_a->next;
	if (write(1, "ra\n", ft_strlen("ra\n")) < 0)
		return (-1);
	return (0);
}

int	rb(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	if ((ps->bottom_b == 0) || (ps->top_b == 0))
		return (-2);
	ps->bottom_b = ps->top_b;
	ps->top_b = ps->top_b->next;
	if (write(1, "rb\n", ft_strlen("rb\n")) < 0)
		return (-1);
	return (0);
}
