/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:42:28 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 16:28:55 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_hex(unsigned char *addr, unsigned int cnt)
{
	char			*base;
	unsigned char	hex_array[41];
	unsigned int	idx;
	unsigned int	addr_idx;

	base = "0123456789abcdef";
	idx = 0;
	while (idx < sizeof(hex_array))
		hex_array[idx++] = ' ';
	idx = 0;
	addr_idx = 0;
	while (addr_idx < cnt)
	{
		if (idx % 5 != 0)
		{
			hex_array[idx++] = base[(addr[addr_idx]) / 16];
			hex_array[idx++] = base[(addr[addr_idx]) % 16];
			addr_idx++;
		}
		else
			idx++;
	}
	write(1, hex_array, sizeof(hex_array));
}

void	print_address(unsigned long int num)
{
	char			*base;
	char			address[16];
	unsigned int	idx;

	base = "0123456789abcdef";
	idx = 0;
	while (idx < (unsigned int)(sizeof(address)))
		address[idx++] = '0';
	idx = sizeof(address) - 1;
	while (num > 0)
	{
		address[idx] = base[num % 16];
		num = num / 16;
		idx--;
	}
	write(1, address, sizeof(address));
	write(1, ":", 1);
}

void	print_ascii(unsigned char *addr, unsigned int cnt)
{
	unsigned int	idx;
	unsigned char	ch;

	idx = 0;
	while (idx < cnt)
	{
		ch = addr[idx];
		if ((ch >= 32) && (ch <= 126))
			write(1, &ch, 1);
		else
			write(1, ".", 1);
		idx++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	print_cnt;
	unsigned char	*tmp_addr;

	tmp_addr = (unsigned char *)addr;
	print_cnt = size;
	while (size > 0)
	{
		print_address((unsigned long int)tmp_addr);
		if (size >= 16)
			print_cnt = 16;
		else
			print_cnt = size;
		print_hex(tmp_addr, print_cnt);
		print_ascii(tmp_addr, print_cnt);
		tmp_addr += 16;
		size -= print_cnt;
		write(1, "\n", 1);
	}
	return (addr);
}
