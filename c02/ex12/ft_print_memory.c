/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:50:53 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/19 02:09:46 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <string.h>
#include <unistd.h>


char	int_to_hex(long int num)
{
	char ch;
	if( num >= 10 && num <= 15)
	{
		ch = num - 10 + 'a';
	}
	else
	{
		ch = num + '0';
	}
	return ch;
}


void	non_padd_print_hex(long int num)
{
	char ch;

	if (num == 0)
	{
		return ;
	}
	
	non_padd_print_hex(num / 16);
	ch = int_to_hex(num % 16);
	write(1, &ch, 1);
}

int get_num_of_hex_digit(long int num)
{
	int cnt_hex_digit;

	if (num == 0)
	{
		return 0;
	}

	return get_num_of_hex_digit( num / 16) + 1;
}


void zero_padding_print(int num)
{
	int idx;

	idx = 0;
	while( idx < num)
	{
		write(1, "0", 1);
		idx++;
	}
}

void print_hex(long int num, int digits)
{
	int num_of_zero_padding;

	num_of_zero_padding = digits - get_num_of_hex_digit(num);

	if( num_of_zero_padding > 0)
	{
		zero_padding_print(num_of_zero_padding);
	}
	non_padd_print_hex(num);
}


void print_asci(char ch)
{
	if( (ch >= 0 && ch <=31) || ch == 127)
	{
		write(1, ".", 1);
	}
	else
	{
		write(1, &ch, 1);
	}

}


void *ft_print_memory(void *addr, unsigned int size)
{

	int zero_pad_cnt;
	int num_of_digit;
	int idx;
	int hex_cnt;
	int tmp_idx;

	if( size == 0)
	{
		return addr;
	}

	idx = 0;
	while( idx < size)
	{
		if( idx % 16 == 0)
		{
			print_hex((long int)addr + idx, 16);
			write(1,": ",2);
		}
		
		if( size - idx >= 16)
		{
			hex_cnt = 16;
		}
		else
		{
			hex_cnt = size - idx;
		}

		tmp_idx = 0;
		while( tmp_idx < hex_cnt)
		{
			print_hex(*(char*)(addr+idx),2);
			if( idx % 2 == 1)
			{
				write(1, " ", 1);
			}
			tmp_idx++;
			idx++;
		}
		

		tmp_idx = 0;
		if( hex_cnt < 16)
		{
			while( tmp_idx < 16 - hex_cnt)
			{
				write(1, " ", 1);
				tmp_idx++;
			}
		}

		tmp_idx = 0;
		idx -= hex_cnt;
		while( tmp_idx < hex_cnt)
		{
			print_asci(*(char*)(addr+idx));
			tmp_idx++;
			idx++;
		}

		write(1, "\n", 1);
	}
	return addr;
}


int main(void)
{

	char str[] = { 0x42, 0x6f, 0x6e, 0x6a, 0x6f, 0x75, 0x72, 0x20, 0x6c, 0x65, 0x73, 0x20, 0x61, 0x6d, 0x69, 0x6e, 0x63, 0x68, 0x65, 0x73, 0x09, 0x0a, 0x09, 0x63, 0x20, 0x20, 0x65, 0x73, 0x74, 0x20, 0x66, 0x6f, 0x75, 0x09, 0x74, 0x6f, 0x75, 0x74, 0x09, 0x63, 0x65, 0x20, 0x71, 0x75, 0x20, 0x6f, 0x6e, 0x20, 0x70, 0x65, 0x75, 0x74, 0x20, 0x66, 0x61, 0x69, 0x72, 0x65, 0x20, 0x61, 0x76, 0x65, 0x63, 0x09, 0x0a, 0x09, 0x70, 0x72, 0x69, 0x6e, 0x74, 0x5f, 0x6d, 0x65, 0x6d, 0x6f, 0x72, 0x79, 0x0a, 0x0a, 0x0a, 0x09, 0x6c, 0x6f, 0x6c, 0x2e, 0x6c, 0x6f, 0x6c, 0x0a, 0x20, 0x00 };
	ft_print_memory(str,sizeof(str));
}
