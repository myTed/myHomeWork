/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:32:54 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/18 11:20:14 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	char	ch;

	while (1)
	{
		ch = *str++;
		if (ch == 0)
		{
			break ;
		}
		if (!(ch >= 'a' && ch <= 'z'))
		{
			return (0);
		}
	}
	return (1);
}
