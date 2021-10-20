/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 02:21:57 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:28:38 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
*/
int	ft_strlen(const char *src)
{
	unsigned int	idx;

	idx = 0;
	while (src[idx] != 0)
		idx++;
	return (idx);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	idx;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	idx = 0;
	while (src[idx] != 0 && idx + dst_len + 1 < size)
	{
		dest[dst_len + idx] = src[idx];
		idx++;
	}
	dest[dst_len + idx] = 0;
	if (size < dst_len)
		return (src_len + size);
	else
		return (dst_len + src_len);
}
/*
int	main(void)
{
	char dest1[20] = "ajsdkf";
	char dest2[20] = "ajsdkf";
	char src[20] = "AAAA";
	printf("strlcat    :%ld\n",strlcat(dest1,src,2));
	printf("%s\n",dest1);	
	printf("ft_strlcat :%d\n",ft_strlcat(dest2,src,2));
	printf("%s\n",dest2);
}
*/
