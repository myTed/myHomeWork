/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:34:02 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 22:11:04 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <string.h>
*/
int	ft_strlen(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
		idx++;
	return (idx);
}
/*
int	main(void)
{
	char	*str = "asjdkf";
	printf("ft_str: %s:%d\n",str,ft_strlen(str));
	printf("str   : %s:%ld\n",str,strlen(str));
	
	return (0);
}
*/
