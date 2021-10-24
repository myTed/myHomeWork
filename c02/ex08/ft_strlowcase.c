/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:38:11 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 10:41:17 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
char	*ft_strlowcase(char *str)
{
	char	ch;
	int		idx;

	idx = 0;
	while (str[idx] != 0)
	{
		ch = str[idx];
		if (ch >= 'A' && ch <= 'Z')
		{
			str[idx] = ch - 'A' + 'a';
		}
		idx++;
	}
	return (str);
}
/*
int	main(void)
{
	char buf[128] = "asdfasdfABC*^&asdjfklCCC";
	printf("%s\n", ft_strlowcase(buf));
}
*/
