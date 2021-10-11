/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_reverse_alphabet.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:30:56 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/11 15:58:54 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_reverse_alphabet(void)
{
	int	idx;
	int	c;

	idx = 0;
	c = 'z';
	while (1)
	{
		if (idx < 'z' - 'a' + 1)
		{
			write(1, &c, 1);
			c--;
			idx++;
		}
		else
		{
			break ;
		}
	}
	return ;
}
