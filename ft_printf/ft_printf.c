#include <stdio.h>
#include "ft_printf.h"
#include <unistd.h>

static void fill_func_arry(t_func *pfunc_arry)
{
	pfunc_arry[0].op = 's';
	pfunc_arry[0].opfunc = type_s_printf;
	pfunc_arry[1].op = 'c';
	pfunc_arry[1].opfunc = type_c_printf;
	pfunc_arry[2].op = 'p';
	pfunc_arry[2].opfunc = type_p_printf;
	pfunc_arry[3].op = 'd';
	pfunc_arry[3].opfunc = type_d_printf;
	pfunc_arry[4].op = 'i';
	pfunc_arry[4].opfunc = type_d_printf;
	pfunc_arry[5].op = 'u';
	pfunc_arry[5].opfunc = type_u_printf;
	pfunc_arry[6].op = 'x';
	pfunc_arry[6].opfunc = type_x_printf;
	pfunc_arry[7].op = 'X';
	pfunc_arry[7].opfunc = type_X_printf;
	pfunc_arry[8].op = '%';
	pfunc_arry[8].opfunc = type_percent_printf;
}

static int	print_type(
				t_func *pfunc_arry,
				va_list *pap,
				const char ch, 
				int *pw_cnt
				){
	int	idx;

	if (ch <= 0)
		return (-2);
	idx = 0;
	while (idx < MAX_OPTION_NUM)
	{
		if (pfunc_arry[idx].op == ch)
		{
			*pw_cnt = (pfunc_arry[idx].opfunc)(pap);
			return (0);
		}
		idx++;
	}
	return (-1);
}

static int	print_not_type(const char ch, int *pw_cnt)
{	
	ssize_t	result;

	result = write(1, &ch, 1);
	if (result < 0)
		return (-1);
	(*pw_cnt)++;
	return (0);
}

static int	print_arg(const char *str, t_func *pfunc_arry, va_list *pap)
{
	int	idx;
	int	wr_cnt;
	int	result;

	idx = 0;
	wr_cnt = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '%')
		{
			result = print_type(pfunc_arry, pap, str[idx + 1], &wr_cnt);
			if (result < -1)
				break ;
			if (result == 0)
				idx++;
		}
		else
		{
			if (print_not_type(str[idx], &wr_cnt) < 0) 
				break ;
		}
		idx++;
	}
	return (wr_cnt);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	t_func		s_func_arry[MAX_OPTION_NUM];
	int			wr_cnt;

	fill_func_arry(s_func_arry);
	va_start(ap, str);
	wr_cnt = print_arg(str, s_func_arry, &ap);
	va_end(ap);
	return (wr_cnt);
}

int	main(void)
{
	ft_printf("%saksld;fkl%sasdjkf%s\n","KKK","AAA", "KKK");
	ft_printf("%\n");
	ft_printf("%%\n");
	ft_printf("%%%\n");
	ft_printf("%%%%\n");

	ft_printf("123d: %d\n", 123);
	ft_printf("-123d: %d\n", -123);
	ft_printf("123u: %u\n", 123);
	ft_printf("-123u: %u\n", -123);
	ft_printf("123x: %x\n", 123);
	ft_printf("-123x: %x\n", -123);
	ft_printf("MAX i: %d\n", 2147483647);
	ft_printf("MAX -i: %d\n", -2147483648);
	ft_printf("MAX -i-1: %d\n", -2147483649);
	ft_printf("MAX i+1: %d\n", 2147483648);
	ft_printf("MAX i+2: %d\n", 2147483649);
	ft_printf("%p\n", (char*)0x100045);
	int	tmp;

	tmp = 3;
	ft_printf("%p\n", &tmp);
	ft_printf("MAX -l: %d\n",-9223372036854775808);
	printf("MAX -l:%d\n",-9223372036854775808);
	ft_printf("MAX +l: %d\n", 9223372036854775807);
	printf("MAX +l:%d\n",9223372036854775807);
	ft_printf("MAX -u: %u\n",-9223372036854775808);
	printf("MAX -u:%u\n",-9223372036854775808);
	ft_printf("MAX +u: %u\n", 9223372036854775807);
	printf("MAX +u:%u\n",9223372036854775807);
}

/*
int	main(void)
{
	ft_printf("%%%\n");
	printf("%%%\n");
	printf("%\n");
	printf("%%\n");
	printf("%%%%\n");
	
	printf("=============\n");
	ft_printf("%%%\n");
	ft_printf("%\n");
	ft_printf("%%\n");
	ft_printf("%%%%\n");
	ft_printf("%sasdjfkljksldf%d\n","kkkkk", 123);	
	
	return (0);
}
*/
/*
int	main(void)
{
	char	*str1;
	char	*str2;
	char	ch;
	int		num;
	int		num2;
	
	str1 = "KKKK";
	str2 = "AAAA";
	ch = 'O';
	num = 0;
	num2 = 0x1234abc;
	ft_printf("%d\n",ft_printf("asjdklfj%s%%1123%s%c%s\n",str1, str2, ch, str1));
	ft_printf("%p\n",(char*)0);
	printf("%p\n",(char*)0);
	printf("%d\n",ft_printf("%i", num));
	ft_printf("%d\n", num);
	ft_printf("%u\n", num);
	ft_printf("%p\n", &num);
	ft_printf("%x\n", num);
	ft_printf("%X\n", num2);
	printf("==========================\n");
	printf("%d\n",printf("%i", num));
	printf("%d\n",printf("asjdklfj%s%%1123%s%c%s\n",str1, str2, ch, str1));
	//printf("%s\n",(char*)0);
	ft_printf("%s\n",(char*)0);
	//printf("%s\n",(char*)0);
	//printf("%u\n", num);
	//printf("%p\n", &num);
	//printf("%x\n", num);
	//printf("%X\n", num2);
	return (0);
}
*/
/*
int	main(void)
{
	ft_printf("%d\n",ft_printf("%"));
	return (0);
}
*/
