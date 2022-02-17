#include "ft_printf.h"
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	idx;
	idx = 0;
	while (str[idx] != 0)
		idx++;
	return (idx);
}
/*
int	ft_putnbr(int n, int is_unsigned, int base, char *base_str)
{
	char    ch;
	long	long_number;
	int		len;

	len = 0;
	if (n < 0)
	{
		if (is_unsigned)
			long_number = ((unsigned long)(n) << 32) >> 32;
		else
			long_number = (long)n * -1;
	}
	else
		long_number = n;
	if (long_number / base != 0)
		len = ft_putnbr(long_number / base, is_unsigned, base, base_str);
	ch = base_str[(long_number % base)];
	write(1, &ch, 1);
	return (++len);
}
*/

int	ft_putnbr(unsigned long long_number, int is_unsigned, int base, char *base_str)
{
	char    ch;
	int		len;

	len = 0;
	if (long_number / base != 0)
		len = ft_putnbr(long_number / base, is_unsigned, base, base_str);
	ch = base_str[(long_number % base)];
	write(1, &ch, 1);
	return (++len);
}

int	type_u_printf(va_list *pap)
{
	unsigned int	tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 10, "0123456789"));
}
/*
int	type_p_printf(va_list *pap)
{
	size_t	tmp;
	int		len;
	int		sh_num;

	tmp = va_arg(*pap, size_t);
	write(1, "0x", 2);
	len = 2;
	if (tmp >> 32 != 0)
	{
		len += ft_putnbr(tmp >> 32, 1, 16, "0123456789abcdef");
		sh_num = 28;
		while ((!((unsigned int)tmp & (0xf << sh_num))) && (sh_num != 0))
		{
			write(1, "0", 1);
			len++;
			sh_num -= 4;
		}
	}
	len += ft_putnbr(tmp, 1, 16, "0123456789abcdef");
	return (len);
}
*/
int	type_p_printf(va_list *pap)
{
	size_t	tmp;
	int		len;

	tmp = va_arg(*pap, size_t);
	write(1, "0x", 2);
	len = 2;
	len += ft_putnbr(tmp, 1, 16, "0123456789abcdef");
	return (len);
}

int	type_percent_printf(va_list *pap)
{
	(void)(pap);
	write(1, "%", 1);
	return (1);
}
