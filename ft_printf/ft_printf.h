#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define MAX_OPTION_NUM	9
# include <stdarg.h>
# include <stddef.h>

typedef int	(*t_opfunc)(va_list *ap, int *perr_status);
typedef struct s_func
{
	char		op;
	t_opfunc	opfunc;
}	t_func;

size_t	ft_strlen(const char *str);
int		ft_putnbr(unsigned long uln, int base, char *base_str, int *perr);
int		type_s_printf(va_list *pap, int *perr_status);
int		type_c_printf(va_list *pap, int *perr_status);
int		type_d_printf(va_list *pap, int *perr_status);
int		type_u_printf(va_list *pap, int *perr_status);
int		type_x_printf(va_list *pap, int *perr_status);
int		type_X_printf(va_list *pap, int *perr_status);
int		type_p_printf(va_list *pap, int *perr_status);
int		type_percent_printf(va_list *pap, int *perr_status);
int		ft_printf(const char *str, ...);
#endif
