/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 00:17:53 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 10:18:04 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	idx;

	idx = 0;
	while ((src[idx] != 0) && (idx < n))
	{
		dest[idx] = src[idx];
		idx++;
	}
	while (idx < n)
	{
		dest[idx++] = 0;
	}
	return (dest);
}

/*
int	main(void)
{
	char dest[128];
	
	printf("%s\n",ft_strncpy(dest, "asjdklf",10));
}
*/
