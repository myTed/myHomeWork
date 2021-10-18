/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 23:40:51 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/18 16:18:26 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	int		idx;

	idx = 0;
	while (src[idx] != 0)
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = src[idx];
	return (dest);
}
