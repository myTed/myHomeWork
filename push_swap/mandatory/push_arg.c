


#include "../include/push_swap.h"
#include "../libft/libft.h"

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
		if (ft_isalpha(str[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
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

	idx = 0;
	while (str[idx])
	{		
		idx++;
	}
}

int	arg_check(char *argv[])
{
	int		idx;
	size_t	len;
	char	**split_argv;

	idx = 0;
	while (argv[idx])
	{
		if (is_empty_str(argv[idx]) == 1)
			return (0);
		if (is_char_str(argv[idx]) == 1)
			return (0);
		len = ft_strlen(argv[idx]);
		if (get_space_cnt(argv[idx], &space_cnt) < 0)
			return (0);
		if (len == space_cnt)
			return (0);
		if (space_cnt)
		{
			split_argv = ft_split(argv[idx], ' ');
			if (split_argv == 0)
				return (0);
			is_over_range_int();
		}
	}
}


