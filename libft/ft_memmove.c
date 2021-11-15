/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:37:40 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/11 18:32:07 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp_dest;
	const unsigned char	*tmp_src;
	size_t				idx;

	idx = 0;
	tmp_dest = dest;
	tmp_src = src;
	if (tmp_dest < tmp_src)
	{
		while (idx < n)
		{
			tmp_dest[idx] = tmp_src[idx];
			idx++;
		}
	}
	else
	{
		while (idx < n)
		{
			tmp_dest[n - 1 - idx] = tmp_src[n - 1 - idx];
			idx++;
		}
	}
	return (dest);
}

/*
int	main(void)
{
	char	str[] = "memmove can be very useful......";
	char	str2[]= "memmove can be very useful......";
	char	str3[]= "1234567890";
	ft_memmove(str + 20, str + 15, 11);
	memmove(str2 + 20, str2 + 15, 11);
	ft_memmove(str3+1, str3, 9);
	printf("%s\n",str);
	printf("%s\n",str2);
	printf("%s\n",str3);
	return (0);
}
*/
