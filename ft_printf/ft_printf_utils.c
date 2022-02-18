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

int	ft_putnbr(
		unsigned long long_number,
		int base,
		char *base_str,
		int *perr_status
		){
	char	ch;
	int		len;
	int		tmp_len;

	if (base_str == 0)
		return (-1);
	if (perr_status == 0)
		return (-2);
	len = 0;
	if (long_number / base != 0)
		len = ft_putnbr(long_number / base, base, base_str, perr_status);
	ch = base_str[(long_number % base)];
	tmp_len = write(1, &ch, 1);
	if (tmp_len < 0)
		*perr_status = 1;
	len += tmp_len;
	return (len);
}

int	type_u_printf(va_list *pap, int *perr_status)
{
	unsigned int	tmp;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 10, "0123456789", perr_status));
}

int	type_p_printf(va_list *pap, int *perr_status)
{
	size_t	tmp;
	ssize_t	wr_cnt;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	tmp = va_arg(*pap, size_t);
	wr_cnt = write(1, "0x", 2);
	if (wr_cnt < 0)
	{
		*perr_status = -1;
		return (wr_cnt);
	}
	wr_cnt += ft_putnbr(tmp, 16, "0123456789abcdef", perr_status);
	return (wr_cnt);
}

int	type_percent_printf(va_list *pap, int *perr_status)
{
	ssize_t	wr_cnt;

	(void)(pap);
	if (perr_status == 0)
		return (-1);
	wr_cnt = write(1, "%", 1);
	if (wr_cnt < 0)
		*perr_status = -1;
	return (wr_cnt);
}
