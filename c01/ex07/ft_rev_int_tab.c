/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:47:54 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/14 23:49:36 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_rev_int_tab(int *tab, int size)
{
	int	start_pos;
	int	end_pos;

	start_pos = 0;
	end_pos = size - 1;
	while (start_pos < end_pos)
	{
		swap(&tab[start_pos], &tab[end_pos]);
		start_pos++;
		end_pos--;
	}
}
