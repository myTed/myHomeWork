/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:24:59 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 16:38:20 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
/*
#include <stdio.h>
*/
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
	int				idx;
	unsigned char	ch;

	idx = 0;
	while (str[idx] != 0)
	{
		ch = str[idx];
		if ((ch >= 32) && (ch <= 126))
		{
			write(1, &ch, 1);
		}
		else
		{
			write(1, "\\", 1);
			if (ch <= 15)
			{
				write(1, "0", 1);
			}
			if (ch == 0)
				write(1, "0", 1);
			else
				print_hex(ch);
		}
		idx++;
	}
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("argument has to be 1!\n");
		return (0);
	}
	printf("%s\n",argv[1]);
	ft_putstr_non_printable("Coucou\ttu vas bien ?");
	return (0);
}
*/
