#ifndef CHANGE_MAP_H
#define CHANGE_MAP_H
#define EMPTY_INDEX		0
#define OBSTACLE_INDEX  1
#define OCCUPY_INDEX    2
#include "utils.h"
#include "cal_square.h"
int **make_int_map(t_mark *pmark);
void fill_char_map_to_int_map(char **pchar_map,t_mark *pmark,int **pint_map);
void print_max_square(t_mark *pmark, char **pchar_map, t_coordinate *pmax_square);
void test_print_map(t_mark *pmark,int **pint_map);
#endif
