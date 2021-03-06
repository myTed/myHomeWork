/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:31:57 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/18 11:19:26 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	char	ch;

	while (1)
	{
		ch = *str++;
		if (ch == 0)
		{
			break ;
		}
		if (!(ch >= 0x20 && ch <= 0x7E))
		{
			return (0);
		}
	}
	return (1);
}
