/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:52:16 by kyolee            #+#    #+#             */
/*   Updated: 2021/10/23 19:20:57 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define ROW_MAX 10
#define COL_MAX 10
#define NUM_OF_FOUND	10
/*
#include <stdio.h>
*/
void	fill_forbidden_area(
	int (*pmap)[COL_MAX],
	int row,
	int col,
	int value
){
	int	row_idx;
	int	col_idx;

	row_idx = row + 1;
	col_idx = col;
	while (row_idx < ROW_MAX)
		pmap[row_idx++][col_idx] = value;
	row_idx = row;
	while (row_idx < ROW_MAX)
	{
		if ((col_idx - 1 >= 0) && (row_idx + 1 < ROW_MAX))
			pmap[row_idx + 1][col_idx - 1] = value;
		row_idx++;
		col_idx--;
	}
	row_idx = row;
	col_idx = col;
	while (row_idx < ROW_MAX)
	{
		if ((col_idx + 1 < COL_MAX) && (row_idx + 1 < ROW_MAX))
			pmap[row_idx + 1][col_idx + 1] = value;
		row_idx++;
		col_idx++;
	}
}

void	display_foot_print(
	int *foot_print
){
	int		idx;
	char	ch;

	idx = 0;
	while (idx < COL_MAX)
	{
		ch = foot_print[idx] + '0';
		write(1, &ch, 1);
		idx++;
	}
	write(1, "\n", 1);
}

void	restore_forbidden_area(
	int (*map)[COL_MAX],
	int row,
	int col,
	int *foot_print
){
	int	idx;

	idx = 0;
	fill_forbidden_area(map, row, col, 0);
	while (idx < row)
	{
		fill_forbidden_area(map, idx, foot_print[idx], 1);
		idx++;
	}
}

int	recursive_queen_print(
	int (*map)[COL_MAX],
	int row,
	int col,
	int *foot_print
){
	int	idx;

	idx = 0;
	if (row >= ROW_MAX)
	{
		display_foot_print(foot_print);
		foot_print[NUM_OF_FOUND]++;
		return (1);
	}
	while (idx < COL_MAX)
	{	
		if (map[row][col] == 0)
		{
			foot_print[row] = col;
			fill_forbidden_area(map, row, col, 1);
			if (recursive_queen_print(map, row + 1, 0, foot_print) == 0)
				restore_forbidden_area(map, row, col, foot_print);
		}
		idx++;
		col++;
	}
	return (0);
}

int	ft_ten_queens_puzzle(void)
{
	int	map[ROW_MAX][COL_MAX];
	int	foot_print[COL_MAX + 1];
	int	num;
	int	idx_row;
	int	idx_col;

	num = 0;
	foot_print[NUM_OF_FOUND] = num;
	idx_row = 0;
	while (idx_row < ROW_MAX)
	{
		idx_col = 0;
		while (idx_col < COL_MAX)
		{
			map[idx_row][idx_col] = 0;
			idx_col++;
		}
		idx_row++;
	}
	recursive_queen_print(map, 0, 0, foot_print);
	num = foot_print[NUM_OF_FOUND];
	return (num);
}

/*
int	main(void)
{
	int num;

	num = ft_ten_queens_puzzle();

	printf("\n");
	printf("%d\n",num);
	return (0);
}
*/
