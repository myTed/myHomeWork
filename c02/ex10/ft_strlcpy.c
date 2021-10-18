/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:36:31 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/18 16:17:33 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	idx;
	int	len;

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
