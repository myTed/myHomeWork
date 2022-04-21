#include "ft_printf.h"
#include <unistd.h>

int	type_s_printf(va_list *pap, int	*perr_status)
{
	char		*ptmp;
	size_t		tmp_len;
	ssize_t		wr_cnt;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	wr_cnt = 0;
	ptmp = va_arg(*pap, char *);
	if (ptmp == 0)
	{
		wr_cnt = write(1, "(null)", 6);
		if (wr_cnt < 0)
			*perr_status = -1;
		return (wr_cnt);
	}
	tmp_len = ft_strlen(ptmp);
	wr_cnt = write(1, ptmp, tmp_len);
	if (wr_cnt < 0)
		*perr_status = -1;
	return (wr_cnt);
}

int	type_c_printf(va_list *pap, int *perr_status)
{
	unsigned char	tmp;
	ssize_t			wr_cnt;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	tmp = (unsigned char)va_arg(*pap, int);
	wr_cnt = write(1, &tmp, 1);
	if (wr_cnt < 0)
		*perr_status = -1;
	return (wr_cnt);
}

int	type_d_printf(va_list *pap, int *perr_status)
{
	int				tmp;
	ssize_t			wr_cnt;
	unsigned long	ultmp;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	wr_cnt = 0;
	tmp = va_arg(*pap, int);
	if (tmp < 0)
	{
		wr_cnt = write(1, "-", 1);
		if (wr_cnt < 0)
		{
			*perr_status = -1;
			return (-1);
		}
		ultmp = (-1) * (unsigned long)(tmp);
	}
	else
		ultmp = tmp;
	wr_cnt += ft_putnbr(ultmp, 10, "0123456789", perr_status);
	return (wr_cnt);
}

int	type_x_printf(va_list *pap, int *perr_status)
{
	unsigned int	tmp;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 16, "0123456789abcdef", perr_status));
}

int	type_X_printf(va_list *pap, int *perr_status)
{
	unsigned int	tmp;

	if ((pap == 0) || (perr_status == 0))
		return (-1);
	tmp = va_arg(*pap, unsigned int);
	return (ft_putnbr(tmp, 16, "0123456789ABCDEF", perr_status));
}
