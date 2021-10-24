/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:58:50 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/23 22:05:44 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	idx;

	if (argc != 1)
		return (0);
	idx = 0;
	while (argv[0][idx] != 0)
	{
		write(1, &argv[0][idx], 1);
		idx++;
	}
	write(1, "\n", 1);
	return (0);
}
