#ifndef CAL_SQUARE_H
#define CAL_SQUARE_H
#include "mark.h"
typedef struct coordinate
{
	int	start_row_idx;
	int	start_col_idx;
	int end_row_idx;
	int	end_col_idx;
	int	max_value;
}t_coordinate;

int is_possible_cal(int row_idx,int col_idx);
int get_mininum_value(int **pint_map,int row_idx,int col_idx);
int cal_square(Mark *pmark,int **pint_map);
void get_coordinate_max_square(Mark *pmark, int **pint_map, int max_value, t_coordinate *pmax_square);
#endif
