#include "push_swap.h"

int	is_already_ordered_stack_a(t_stack *ps, int n)
{
	int		idx;
	t_list	*ptmp_top;

	ptmp_top = ps->top_a;
	idx = 0;
	while (idx < n - 1)
	{
		if (ptmp_top->data > ptmp_top->next->data)
			return (0);
		idx++;
		ptmp_top = ptmp_top->next;
	}
	return (1);
}

int	is_already_ordered_stack_b(t_stack *ps, int n)
{
	int		idx;
	t_list	*ptmp_top;

	ptmp_top = ps->top_b;
	idx = 0;
	while (idx < n - 1)
	{
		if (ptmp_top->data < ptmp_top->next->data)
			return (0);
		idx++;
		ptmp_top = ptmp_top->next;
	}
	return (1);
}

int	is_only_data_more_than_two_third_pivot(
		t_stack *ps,
		t_pivot *ppv,
		int start_idx,
		int end_idx
){
	int		idx;
	t_list	*tmp_top;

	if (ps == 0)
		return (-1);
	idx = start_idx;
	tmp_top = ps->top_a;
	while (idx < end_idx)
	{
		if (tmp_top->data < ppv->two_third_pivot)
			return (0);
		idx++;
		tmp_top = tmp_top->next;
	}
	return (1);
}

int	is_only_data_less_than_one_third_pivot(
		t_stack *ps,
		t_pivot *ppv,
		int start_idx,
		int end_idx
){
	int		idx;
	t_list	*tmp_top;

	if (ps == 0)
		return (-1);
	idx = start_idx;
	tmp_top = ps->top_b;
	while (idx < end_idx)
	{
		if (tmp_top->data > ppv->one_third_pivot)
			return (0);
		idx++;
		tmp_top = tmp_top->next;
	}
	return (1);
}
