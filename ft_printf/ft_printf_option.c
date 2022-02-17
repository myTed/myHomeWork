#include "ft_printf.h"
#include <unistd.h>

int type_s_printf(va_list *pap)
{
	char    *tmp;
	size_t  tmp_len;

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

int type_c_printf(va_list *pap)
{
	unsigned char   tmp;
	size_t  tmp_len;

	tmp = (unsigned char)va_arg(*pap, int);
	tmp_len = 1;
	write(1, &tmp, tmp_len);
	return (tmp_len);
}

int type_d_printf(va_list *pap)
{
	int     		tmp;
	int     		len;
	unsigned long	ultmp;

	len = 0;
	tmp = va_arg(*pap, int);
	if (tmp < 0)
	{
		write(1, "-", 1);
		len++;
		ultmp = tmp * -1;
		ultmp &= 0x00000000ffffffff;
	}
	else
		ultmp = tmp;
	len += ft_putnbr(ultmp, 0, 10, "0123456789");
	return (len);
}

int type_x_printf(va_list *pap)
{
	unsigned int    tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 16, "0123456789abcdef"));
}

int type_X_printf(va_list *pap)
{
	unsigned int    tmp;
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 1, 16, "0123456789ABCDEF"));
}
