/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 00:49:47 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/20 01:03:33 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *src)
{
	int	idx;

	idx = 0;
	while (src[idx] != 0)
		idx++;
	return (idx);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int	idx;
	int	len;

	idx = 0;
	len = ft_strlen(dest);
	while (src[idx] != 0 && idx < nb)
	{
		dest[len + idx] = src[idx];
		idx++;
	}
	dest[len + idx] = 0;
	return (dest);
}
/*
int	main(void)
{
	char str1[128] = "AAAAAAAAAAAA1";
	char str2[128] = "AAAAAAAAAAAA1";
	char *str3 = "asjdkfljaksl";

	printf("   strncat:%s\n", strncat(str1, str3,0));
	printf("ft_strncat:%s\n", ft_strncat(str2, str3,0));
	return (0);
}
*/
