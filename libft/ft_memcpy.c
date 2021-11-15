/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:23:56 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/15 11:30:52 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <string.h>
#include <stdio.h>
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		*((unsigned char *)dest + idx) = *((const unsigned char *)src + idx);
		idx++;
	}
	return (dest);
}

/*
int	main(int argc, char *argv[])
{
	char dest[128];
	char dest2[128];

	if (argc != 2)
		return (0);
	printf("%s\n",(char *)ft_memcpy(dest, argv[1], strlen(argv[1]) + 1));
	printf("%s\n",(char *)memcpy(dest2, argv[1], strlen(argv[1]) + 1));

	return (0);
}
*/
