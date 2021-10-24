/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:03:08 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/24 11:15:47 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	is_found_delim(char ch)
{
	if ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z')
		|| (ch >= '0' && ch <= '9')
	)
	{
		return (0);
	}
	return (1);
}

char	lower_to_upper(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch = ch - 'a' + 'A';
	}
	return (ch);
}

char	upper_to_lower(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		ch = ch - 'A' + 'a';
	}
	return (ch);
}

char	*ft_strcapitalize(char *str)
{
	int		cnt_after_delim;
	int		idx;

	cnt_after_delim = 0;
	idx = 0;
	while (str[idx] != 0)
	{
		if (is_found_delim(str[idx]))
		{
			cnt_after_delim = 0;
		}
		else
		{
			cnt_after_delim++;
		}
		if (cnt_after_delim == 1)
			str[idx] = lower_to_upper(str[idx]);
		else
			str[idx] = upper_to_lower(str[idx]);
		idx++;
	}
	return (str);
}

/*
int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("argument has to be 1");
		return (0);
	}

	printf("%s\n",ft_strcapitalize(argv[1]));
}
*/
