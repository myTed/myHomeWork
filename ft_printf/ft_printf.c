#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	idx;
	idx = 0;
	while (str[idx++] != 0);
	return (idx - 1);
}

int type_s_print(va_list *pap)
{
	char 	*tmp;
	size_t	tmp_len;

	tmp = va_arg(*pap, char *);
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
/*
int	type_d_printf(va_list *pap)
{
	int		tmp;

	tmp = va_arg(*pap, int);

}
*/
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
	//pfunc_arry['d'] = type%d_printf;
}

int	ft_printf(const char	*str, ...)
{
	va_list	ap;
	int (*func_arry[256])(va_list *ap);
	int	(*pfunc)(va_list *ap);
	int	written_cnt;
	int	idx;

	init_func_arry(func_arry, 256);
	add_type_proc(func_arry);

	va_start(ap, str);
	written_cnt = 0;
	idx = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '%')
		{
			pfunc = func_arry[(unsigned const char)str[idx+1]];
			if (pfunc)
				(*pfunc)(&ap);
			else
				write(1, &str[idx], 1);
		}
		else
			write(1, &str[idx], 1);
		idx++;
	}
	va_end(ap);
	return (written_cnt);
}

int	main(void)
{
	char	*str1;
	char	*str2;
	char	ch;
	int		num;

	str1 = "KKKK";
	str2 = "AAAA";
	ch = 'O';
	num = 100;
	ft_printf("asjdklfj%s1123%s\n%c",str1, str2, ch);
	return (0);
}
