
#include "push_swap.h"
#include "../libft/libft.h"



static int	sort_size_under_2(t_stack *ps)
{
	if (ps == 0)
		return (-1);
	return (sort_size_2_big(ps));
}

static int	sort_size_under_3(t_stack *ps)
{
	int	max_idx;

	if (ps == 0)
		return (-1);
	if (find_maximum_value_idx(ps->top_a, 3, &max_idx) < 0)
		return (-1);
	if (max_idx == 0)
	{
		ra(ps);
		return (sort_size_under_2(ps));
	}
	else if (max_idx == 1)
	{
		rra(ps);
		return (sort_size_under_2(ps));
	}
	else
		return (sort_size_under_2(ps));
}

static int	sort_size_under_4(t_stack *ps)
{
	int	min_idx;

	if (ps == 0)
		return (-1);
	if (find_minimum_value_idx(ps->top_a, 4, &min_idx) < 0)
		return (-1);
	if (min_idx == 1)
		ra(ps);
	else if (min_idx == 2)
	{
		ra(ps);
		ra(ps);
	}
	else if (min_idx == 3)
		rra(ps);
	pb(ps);
	if (sort_size_under_3(ps) < 0)
		return (-1);
	pa(ps);
	return (0);
}

static int	sort_size_under_5(t_stack *ps)
{
	int	min_idx;

	if (ps == 0)
		return (-1);
	if (find_minimum_value_idx(ps->top_a, 5, &min_idx) < 0)
		return (-1);
	if (min_idx == 1)
		ra(ps);
	else if (min_idx == 2)
	{
		ra(ps);
		ra(ps);
	}
	else if (min_idx == 3)
	{
		rra(ps);
		rra(ps);
	}
	else if (min_idx == 4)
		rra(ps);
	pb(ps);
	if (sort_size_under_4(ps) < 0)
		return (-1);
	pa(ps);
	return (0);
}

int	sort_size_under_handler(t_stack *ps,int	size)
{
	if (size == 5)
		return (sort_size_under_5(ps));
	else if (size == 4)
		return (sort_size_under_4(ps));
	else if (size == 3)
		return (sort_size_under_3(ps));
	else if (size == 2)
		return (sort_size_under_2(ps));
	else
		return (0);
}

