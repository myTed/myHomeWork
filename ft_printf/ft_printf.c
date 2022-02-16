//#include <stdio.h>
#include "ft_printf.h"

int	printf_type(PFUNC_ARRY func_arry, const char *str, int *pidx, int *pw_cnt)
{
	int	idx;
	int	(*pfunc)(va_list *ap);
	
	idx = *pidx;
	if (str[idx + 1] == 0)
		return (-1);
	pfunc = func_arry[str[idx + 1]];
	if (pfunc == 0)
		idx++;
	else
	{
		*pw_cnt += (*pfunc)(&ap);
		idx+=2;
	}
	*pidx = idx;
	return (0);
}


int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int (*func_arry[MAX_PROCS_NUM])(va_list *ap);
	int	written_cnt;
	int	idx;

	init_func_arry(func_arry, MAX_PROCS_NUM);
	va_start(ap, str);
	written_cnt = 0;
	idx = 0;
	while (str[idx] != 0)
	{
		if (str[idx] == '%')
			if (printf_type(func_arry, str, &idx, &written_cnt) < 0)
				break;
		else
		{
			write(1, &str[idx], 1);
			written_cnt++;
		}
		idx++;
	}
	va_end(ap);
	return (written_cnt);
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
