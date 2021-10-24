/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 22:15:54 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/23 22:21:31 by kyolee           ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int	idx;

	idx = 1;
	while (idx < argc)
	{
		print_string(argv[argc - idx]);
		idx++;
		write(1, "\n", 1);
	}
	return (0);
}
