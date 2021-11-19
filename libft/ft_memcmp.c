/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 01:18:13 by kyolee            #+#    #+#             */
/*   Updated: 2021/11/18 19:54:58 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
*/
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				idx;
	const unsigned char	*src1;
	const unsigned char	*src2;

	idx = 0;
	src1 = s1;
	src2 = s2;
	while (idx < n)
	{
		if (src1[idx] > src2[idx])
			return (1);
		else if (src1[idx] < src2[idx])
			return (-1);
		else
			idx++;
	}
	return (0);
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 4)
		return 0;
	printf("%d\n",ft_memcmp(argv[1], argv[2], atoi(argv[3])));
	printf("%d\n",memcmp(argv[1], argv[2], atoi(argv[3])));
}
*/
