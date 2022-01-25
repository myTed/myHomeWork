//#include <stdio.h>
#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	idx;
	idx = 0;
	while (str[idx++] != 0);
	return (idx - 1);
}

int	put_number_base(int n, int is_unsigned, int base, char *base_str)
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
		len = put_number_base(long_number / base, is_unsigned, base, base_str);
	ch = base_str[(long_number % base)];
	write(1, &ch, 1);
	return (++len);
}

int    ft_putnbr(int n, int is_unsigned, int base, char *base_str)
{
	int len;

	len = put_number_base(n, is_unsigned, base, base_str);
	return (len);
}

int type_s_print(va_list *pap)
{
	char 	*tmp;
	size_t	tmp_len;

	tmp = va_arg(*pap, char *);
	if (tmp == 0)
	{
		write(1,"(null)",6);
		return (6);
	}
	tmp_len = ft_strlen(tmp);
	write(1, tmp, tmp_len);
	return (tmp_len);
}

int	type_c_printf(va_list *pap)
{
	char	tmp;
	size_t	tmp_len;

	tmp = (char)va_arg(*pap, int);
	tmp_len = 1;
	write(1, &tmp, tmp_len);
	return (tmp_len);
}

int	type_d_printf(va_list *pap)
{
	int		tmp;
	int		len;

	len = 0;
	tmp = va_arg(*pap, int);
	if (tmp < 0)
	{
		write(1, "-", 1);
		len++;
	}
	len += ft_putnbr(tmp, 0, 10, "0123456789");
	return (len);
}

int	type_u_printf(va_list *pap)
{
	unsigned int	tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 10, "0123456789"));
}

int	type_x_printf(va_list *pap)
{
	unsigned int	tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 16, "0123456789abcdef"));
}

int	type_X_printf(va_list *pap)
{
	unsigned int	tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 16, "0123456789ABCDEF"));
}

int	type_p_printf(va_list *pap)
{
	size_t	tmp;
	int		len;

	tmp = va_arg(*pap, size_t);
	write(1, "0x", 2);
	len = 2;
	if (tmp >> 32 != 0)
		len += ft_putnbr(tmp >> 32, 1, 16, "0123456789abcdef");
	len += ft_putnbr(tmp, 1, 16, "0123456789abcdef");
	return (len);
}

int	type_percent_printf(va_list *pap)
{
	(void)(pap);
	write(1, "%", 1);
	return (1);
}

void init_func_arry(int (**pfunc_arry)(va_list *), size_t len)
{
	size_t	idx;
	idx = 0;
	while (idx < len)
		pfunc_arry[idx++] = 0;
}

void add_type_proc(int (**pfunc_arry)(va_list *))
{
	pfunc_arry['s'] = type_s_print;
	pfunc_arry['c'] = type_c_printf;
	pfunc_arry['p'] = type_p_printf;
	pfunc_arry['d'] = type_d_printf;
	pfunc_arry['i'] = type_d_printf;
	pfunc_arry['u'] = type_u_printf;
	pfunc_arry['x'] = type_x_printf;
	pfunc_arry['X'] = type_X_printf;
	pfunc_arry['%'] = type_percent_printf;
}

