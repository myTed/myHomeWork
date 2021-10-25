#include "cal_square.h"

int	is_possible_cal(int row_idx,int col_idx)
{
	if ((row_idx -1 >= 0) && (col_idx -1 >= 0))
		return (1);
	return (0);
}


int get_mininum_value(int **pint_map,int row_idx,int col_idx)
{
	unsigned int	idx;
	int min_value;
	int value_array[3];

	if(!is_possible_cal(row_idx,col_idx))
		return pint_map[row_idx][col_idx] - 1;

	value_array[0] = pint_map[row_idx][col_idx -1];
	value_array[1] = pint_map[row_idx -1][col_idx];
	value_array[2] = pint_map[row_idx-1][col_idx-1];
	min_value = value_array[0];
	idx = 1;
	while (idx < (unsigned int)(sizeof(value_array)/sizeof(value_array[0])))
	{
		if( value_array[idx] < min_value)
				min_value = value_array[idx];
		idx++;
	}
	return min_value;
}


void get_coordinate_max_square(Mark *pmark, int **pint_map, int max_value, t_coordinate *pmax_square)
{
	int row_idx;
	int	col_idx;

	row_idx = 0;
	col_idx = 0;
	while (row_idx < pmark->rows)
	{
		col_idx = 0;
		while (col_idx < pmark->cols)
		{
			if (pint_map[row_idx][col_idx] == max_value)
			{
				pmax_square->end_row_idx = row_idx;
				pmax_square->end_col_idx = col_idx;
				pmax_square->start_row_idx = row_idx - (max_value - 1);
				pmax_square->start_col_idx = col_idx - (max_value - 1);
				pmax_square->max_value = max_value;
				return ;
			}
			col_idx++;
		}
		row_idx++;
	}
}


int	cal_square(Mark *pmark,int **pint_map)
{
	int row_idx;
	int	col_idx;
	int	num;
	int	max_value;

	row_idx = 0;
	col_idx = 0;
	max_value = 0;	
	while (row_idx < pmark->rows)
	{
		col_idx = 0;
		while (col_idx < pmark->cols)
		{
			if (pint_map[row_idx][col_idx] != 0)
			{
					num = get_mininum_value(pint_map, row_idx, col_idx);
					pint_map[row_idx][col_idx] = num + 1;
					if (max_value < num + 1)
						max_value = num + 1;
			}
			col_idx++;
		}
		row_idx++;
	}
	return max_value;
}

