/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:04:21 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/27 21:15:58 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_printable(char c)
{
	if (c < 32 || c > 126)
		return (0);
	return (1);
}

int	check_overlap(char c1, char c2, char c3)
{
	if (c1 == c2 || c2 == c3 || c3 == c1)
		return (1);
	return (0);
}

int	is_mark(char c, t_mark M)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (c == M.mark[i])
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_append(char *old, char c)
{
	int		i;
	int		len;
	char	*new;

	len = 0;
	while (old[len])
		len++;
	new = malloc(sizeof(char) * (len + 2));
	i = 0;
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(old);
	return (new);
}
