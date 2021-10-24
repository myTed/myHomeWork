/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 22:22:19 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 09:55:15 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_string(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		write(1, &str[idx], 1);
		idx++;
	}
}

int	is_bigger(char *argv1, char *argv2)
{
	int	idx;

	idx = 0;
	while (argv1[idx] != 0 || argv2[idx] != 0)
	{
		if (argv1[idx] > argv2[idx])
			return (1);
		if (argv1[idx] < argv2[idx])
			return (-1);
		idx++;
	}
	return (0);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	bubble_sort(char **argv)
{
	int	fix_idx;
	int	in_idx;
	int	len;

	len = 0;
	while (argv[len] != 0)
		len++;
	len -= 1;
	fix_idx = 0;
	in_idx = 0;
	while (fix_idx < len - 1)
	{
		in_idx = 0;
		while (in_idx < len - fix_idx - 1)
		{
			if (is_bigger(argv[in_idx + 1], argv[in_idx + 2]) > 0)
				ft_swap(&argv[in_idx + 1], &argv[in_idx + 2]);
			in_idx++;
		}
		fix_idx++;
	}
}

int	main(int argc, char *argv[])
{
	int	idx;

	bubble_sort(argv);
	idx = 1;
	while (idx < argc)
	{
		print_string(argv[idx]);
		idx++;
		write(1, "\n", 1);
	}
	return (0);
}
