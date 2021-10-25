#ifndef CHANGE_MAP_H
#define CHANGE_MAP_H
#define EMPTY_INDEX		0
#define OBSTACLE_INDEX  1
#define OCCUPY_INDEX    2
#include "cal_square.h"
int **make_int_map(Mark *pmark);
void fill_char_map_to_int_map(char **pchar_map,Mark *pmark,int **pint_map);
void print_max_square(Mark *pmark, char **pchar_map, t_coordinate *pmax_square);
#endif
