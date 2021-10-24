/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:38:11 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 10:34:06 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
char	*ft_strupcase(char *str)
{
	char	ch;
	int		idx;

	idx = 0;
	while (str[idx] != 0)
	{
		ch = str[idx];
		if (ch >= 'a' && ch <= 'z')
		{
			str[idx] = ch - 'a' + 'A';
		}
		idx++;
	}
	return (str);
}
/*
int	main(void)
{
	char buf[128] = "asdfjlABC*^&abkq";
	printf("%s\n",ft_strupcase(buf));
}
*/
