/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:36:31 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 11:35:17 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
*/
int	get_len_str(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		idx++;
	}
	return (idx);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	idx;
	int				len;

	idx = 0;
	len = get_len_str(src);
	if (size != 0)
	{
		while (src[idx] != 0 && idx < size - 1)
		{
			dest[idx] = src[idx];
			idx++;
		}
		dest[idx] = 0;
	}
	return (len);
}

/*
int	main(int argc, char *argv[])
{
	char buff[128] = "AAA";
	char buff2[128] = "AAA";
	if (argc != 2)
	{
		printf("argument has to be 1");
		return (0);
	}
	
	ft_strlcpy(buff,argv[1],-200);
	strlcpy(buff2, argv[1], -200);
	printf("ft_lcpy:%s\n",buff);
	printf("lcpy   :%s\n",buff2);
}
*/
