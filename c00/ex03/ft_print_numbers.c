/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:56 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/11 16:20:09 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_numbers(void)
{
	int	idx;
	int	c;

	idx = 0;
	c = '0';
	while (1)
	{
		if (idx < '9' - '0' + 1)
		{
			write(1, &c, 1);
			c++;
			idx++;
		}
		else
		{
			break ;
		}
	}
	return ;
}
