//#include <stdio.h>
//
//void print_array(char* arr, int length)
//{
//	static int is_first_print = 0;
// 
//	if ( is_first_print ) {
//		printf(", ");
//	}
//	
//	is_first_print = 1;
//	for (int i = 0; i < length; i++) {
//		printf("%d", arr[i]);
//	}	
//}
//
//
//void comb(char* arr, int n, int r, int index, int num)
//{
//	if (r == 0) {
//		print_array( arr, 3);
//		return;
//	}
//	if (n < r) {
//		return;
//	}
//	arr[index] = num;
//	
//	comb( arr, n - 1 ,  r - 1, index + 1, num + 1);
//	comb( arr, n - 1 , r, index, num + 1);
//}
//
//
//int	main(void)
//{
//	char arr[3];
//
//	comb(arr, 10, 3, 0, 0);
//	
//	return 0;
//}

//
//#include <stdio.h>
//
//void print_number(int* arr, int length)
//{
//	static int first_print_done = 0;
//	char	print_buffer[6];
//
//	if (first_print_done) {
//		write(1, &", ", 2);
//	}
//	print_buffer[0] = (arr[0] / 10) + '0';
//	print_buffer[1] = (arr[0] % 10) + '0';
//	print_buffer[2] = ' ';
//	print_buffer[3] = (arr[1] / 10) + '0';
//	print_buffer[4] = (arr[1] % 10) + '0';
//	print_buffer[5] = 0;
//	write(1, print_buffer, sizeof(print_buffer));
//	first_print_done = 1;
//}
//
//
//void comb(int* arr, int n, int r, int index, int num)
//{
//	if (r == 0) {
//		print_number( arr, 2);
//		return;
//	}
//	if (n < r) {
//		return;
//	}
//	arr[index] = num;
//	
//	comb( arr, n - 1 ,  r - 1, index + 1, num + 1);
//	comb( arr, n - 1 , r, index, num + 1);
//}
//
//
//void ft_print_comb2(void)
//{
//	int arr[2];
//
//	comb(arr, 100, 2, 0, 0);
//}
//
//int	main(void)
//{
//	ft_print_comb2();
//	
//	return 0;
//}


//#include <stdio.h>
//
//#define MY_INT_MAX	2147483647		
//#define MY_INT_MIN	(-2147483647 - 1)
//	
//void	print_number(int nb)
//{
//	static char tmp_number;
//
//	if (nb == 0) return;
//	print_number(nb / 10);
//	tmp_number = nb % 10 + '0';
//	write(1, &tmp_number, 1);
//}
//
//
//void	ft_putnbr(int nb)
//{
//	if (nb < 0)
//	{
//		if (nb == MY_INT_MIN) {
//			write( 1, "-", 1);
//			print_number( nb / 10 * -1 );
//			write( 1, "8", 1);
//			return;
//		}
//		else
//		{
//			nb *= -1;
//			write( 1, "-", 1);
//		}
//	}
//	print_number(nb);
//}
//
//
//int main(void)
//{
//	int number;
//
//	number = 42;
//	ft_putnbr(number);
//	return (0);
//}

#include <stdio.h>

void print_array(char* arr, int length)
{
	static int is_first_print;
	int i;
	int tmp_char;

	if ( is_first_print ) {
		write(1, ", ", 2);
	}
	
	is_first_print = 1;
	i = 0;
	while (i < length) 
	{
		tmp_char = arr[i++] + '0';
		write(1, &tmp_char, 1);
	}
}


void comb(char* arr, int n, int r, int index, int num, int array_length)
{
	if (r == 0) {
		print_array( arr, array_length);
		return;
	}
	if (n < r) {
		return;
	}
	arr[index] = num;
	
	comb( arr, n - 1 ,  r - 1, index + 1, num + 1, array_length);
	comb( arr, n - 1 , r, index, num + 1, array_length);
}

void ft_print_combn(int number)
{
	char arr[9];
	int array_length = number;
	comb(arr, 10, number, 0, 0, array_length);
}



int	main(void)
{
	int number;

	number = 4;
	ft_print_combn( number );
	return 0;
}
