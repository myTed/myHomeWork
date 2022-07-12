#include "../include/push_swap.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

static int is_empty_str(char *str)
{
	if (str == 0)
		return (-1);
	return (!str[0]);
}

static int is_char_str(char *str)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	while (str[idx])
	{
		if (ft_isalpha(str[idx]))
			return (1);
		idx++;
	}
	return (0);
}

static int get_space_cnt(char *str, size_t	*pspace_cnt)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	*pspace_cnt = 0;
	while (str[idx])
	{
		if (str[idx] == ' ')
			(*pspace_cnt)++;	
		idx++;
	}
	return (0);
}

static int free_split(char **str)
{
	int	idx;

	if (str == 0)
		return (-1);
	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
	return (0);
}

static int	is_over_range_int(char **str)
{
	int	idx;
	long long	num;
	int	overflow;

	idx = 0;
	overflow = 0;
	while (str[idx])
	{		
		num = ft_atol(str[idx], &overflow);
		if (overflow)
			return (-1);
		if ((num > 2147483647) || (num < -2147484648))
			return (-1);
		idx++;
	}
	return (0);
}

static int	malloc_arg_check(char *str, char ***psplit_argv, int *psplited)
{
	size_t	len;
	size_t	space_cnt;

	if (is_empty_str(str) == 1)
		return (-1);
	if (is_char_str(str) == 1)
		return (-1);
	len = ft_strlen(str);
	if (get_space_cnt(str, &space_cnt) < 0)
		return (-1);
	if (len == space_cnt)
		return (-1);
	if (space_cnt)
	{
		*psplit_argv = ft_split(str, ' ');
		if (*psplit_argv == 0)
			return (-1);
		if (is_over_range_int(*psplit_argv))
		{
			free_split(*psplit_argv);
			return (-1);
		}
		*psplited = 1;
	}
	return (0);
}


static int	free_arg_check(char **split_argv)
{
	if (split_argv == 0)
		return (-1);
	if (free_split(split_argv) < 0)
		return (-1);
	return (0);
}

static int	is_duplicated_arg(t_elem	num, t_stack *ps)
{
	t_list	*top;
	size_t	idx;

	top = ps->top_a;
	idx = 0;
	while (idx < ps->a_data_cnt)
	{
		if (num == top->data)
			return (1);
		top = top->next;
		idx++;
	}
	return (0);
}

int	arg_push(t_stack *ps, char *argv[], int idx)
{
	char			**split_argv;
	int				overflow;
	long long int	num;
	int				splited;
	int				ret;

	if ((ps == 0) || (argv == 0))
		return (-1);
	splited = 0;
	while (argv[idx])
	{
		if (malloc_arg_check(argv[idx], &split_argv, &splited) < 0)
			return (-1);
		if (splited)
		{
			ret = arg_push(ps, split_argv, 0);
			if (free_arg_check(split_argv) < 0)
				return (-1);
			if (ret < 0)
				return (-1);
			splited = 0;
		}
		else
		{
			num = ft_atol(argv[idx], &overflow);
			if ((num > 2147483647) || (num < -2147483648))
				return (-1);
			if (is_duplicated_arg((t_elem)num, ps))
				return (-1);
			if (push_bottom(ps, num) < 0)
				return (-1);
			ps->a_data_cnt++;
		}
		idx++;
	}
	return (0);
}
