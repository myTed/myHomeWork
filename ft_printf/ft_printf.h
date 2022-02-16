#ifndef FT_PRINTF_H
#define FT_PRINTF_H
# define MAX_PROCS_NUM	256
# include <stdarg.h>

typedef int (*PFUNCARRY[MAX_PROC_NUM])(va_list *ap);
size_t	ft_strlen(const char *str);
int 	put_number_base(int n, int is_unsigned, int base, char *base_str);
int		ft_putnbr(int n, int is_unsigned, int base, char *base_str);
int		type_s_print(va_list *pap);
int		type_c_printf(va_list *pap);
int		type_d_printf(va_list *pap);
int		type_u_printf(va_list *pap);
int		type_x_printf(va_list *pap);
int		type_X_printf(va_list *pap);
int		type_p_printf(va_list *pap);
int		type_percent_printf(va_list *pap);
void	init_func_arry(int (**pfunc_arry)(va_list *), size_t len);
void	add_type_proc(int (**pfunc_arry)(va_list *));
int		ft_printf(const char *str, ...);		
#endif
