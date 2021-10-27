#include "change_map.h"
#include "cal_square.h"
#include "common.h"

int **make_int_map(t_mark *pmark)
{
	int **pint_map;
	int row_idx;

	pint_map = NULL;
	row_idx = 0;
	pint_map = (int**)malloc(sizeof(int*) * ((pmark->rows) + 1));
	if (pint_map == NULL)
			return NULL;
	while(row_idx < pmark->rows)
	{
		pint_map[row_idx] = (int*)malloc(sizeof(int) * pmark->cols);
		if (pint_map[row_idx] == NULL)
			return NULL;
		row_idx++;
	}
	pint_map[pmark->rows] = 0;
	return pint_map;
}


void fill_char_map_to_int_map(char **pchar_map,t_mark *pmark,int **pint_map)
{
	int row_idx;
	int col_idx;

	row_idx = 0;
	col_idx = 0;

	while (row_idx < pmark->rows)
	{
		col_idx = 0;
		while (col_idx < pmark->cols)
		{
			if(pchar_map[row_idx][col_idx] == pmark->mark[EMPTY_INDEX])
				pint_map[row_idx][col_idx] = 1;
			if(pchar_map[row_idx][col_idx] == pmark->mark[OBSTACLE_INDEX])
				pint_map[row_idx][col_idx] = 0;
			col_idx++;
		}
		row_idx++;
	}
}

void print_max_square(t_mark *pmark, char **pchar_map, t_coordinate *pmax_square)
{
	int	row_idx;
	int	col_idx;

	row_idx = 0;
	col_idx = 0;
	while (row_idx < pmark->rows)
	{
		col_idx = 0;
		while (col_idx < pmark->cols)
		{
			if ((row_idx >= pmax_square->start_row_idx) && (row_idx <= pmax_square->end_row_idx)
				&& (col_idx >= pmax_square->start_col_idx) && (col_idx <= pmax_square->end_col_idx))
				write(1, &pmark->mark[OCCUPY_INDEX], 1);
			else
				write(1, &pchar_map[row_idx][col_idx], 1);
			col_idx++;
		}
		write(1,"\n", 1);
		row_idx++;
	}
}

