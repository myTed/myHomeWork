/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:59:02 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/15 01:00:02 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	idx;
	int	fixed_num_cnt;

	fixed_num_cnt = 0;
	while (fixed_num_cnt < size - 1)
	{
		idx = 0;
		while (idx < size - 1 - fixed_num_cnt)
		{
			if (tab[idx] > tab[idx + 1])
			{
				swap(&tab[idx], &tab[idx + 1]);
			}
			idx++;
		}
		fixed_num_cnt++;
	}
}
