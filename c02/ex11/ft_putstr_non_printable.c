/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:24:59 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/18 20:48:58 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	char_to_hex(char ch)
{
	if (ch >= 10 && ch <= 15)
	{
		ch = ch - 10 + 'a';
	}
	else
	{
		ch += '0';
	}
	return (ch);
}

void	print_hex(char ch)
{
	if (ch == 0)
	{
		return ;
	}
	print_hex(ch / 16);
	ch = char_to_hex(ch % 16);
	write(1, &ch, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		if (str[idx] >= 0 && str[idx] <= 31 || str[idx] == 127)
		{
			write(1, "\\", 1);
			if (str[idx] >= 0 && str[idx] <= 15)
			{
				write(1, "0", 1);
			}
			if (str[idx] == 0)
				write(1, "0", 1);
			else
				print_hex(str[idx]);
		}
		else
			write(1, &str[idx], 1);
		idx++;
	}
}
