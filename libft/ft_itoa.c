/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:22:05 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/22 14:19:22 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#define MAX_INT_STR_LEN 11
/*
#include <stdio.h>
*/
int	fill_number(char *str, int n, int *pis_negative)
{
	long long int	long_num;
	int				idx;

	idx = 0;
	if (n < 0)
	{
		long_num = (long long int)n * -1;
		*pis_negative = 1;
	}
	else
		long_num = n;
	if (long_num / 10 != 0)
		idx = fill_number(str, long_num / 10, pis_negative);
	if (idx == 0 && *pis_negative)
		str[idx++] = '-';
	str[idx] = (long_num % 10) + '0';
	return (++idx);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			idx;
	int			is_negative;

	idx = 0;
	is_negative = 0;
	str = malloc(sizeof(char) * (MAX_INT_STR_LEN + 1));
	if (str == NULL)
		return (NULL);
	idx = fill_number(str, n, &is_negative);
	str[idx] = 0;
	return (str);
}
/*
int	main(int argc, char *argv[])
{
	int num;
	if (argc != 2)
		return (0);
	num = atoi(argv[1]);
	printf("%s\n",ft_itoa(num));
}
*/
