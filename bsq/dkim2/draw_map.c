#include "common.h"
#include "utils.h"
#include "change_map.h"
#include "error.h"

void free_int_map(int **map)
{
    int idx;
    
    idx = 0;
    while(map[idx] != NULL)
    {   
        free(map[idx]);
        idx++;
    }   
    free(map);
}

void free_char_map(char **map)
{
    int idx;

    idx = 0;
    while (map[idx] != NULL)
    {
        free(map[idx]);
        idx++;
    }   
    free(map);
}

void draw_maxim_square_from_map(char **pchar_map,t_mark *pmark)
{
    int **pint_map;
    int max_value;
    t_coordinate max_square;

    pint_map = make_int_map(pmark);
    if (pint_map == NULL)
    {   
        write(2, MEMORY_ERROR_MSG, MEMORY_ERROR_MSG_LEN);
        exit(1);
    }   
    fill_char_map_to_int_map(pchar_map, pmark, pint_map);
    max_value = cal_square(pmark, pint_map);
    get_coordinate_max_square(pmark, pint_map, max_value, &max_square);
    print_max_square(pmark, pchar_map, &max_square);
    free_int_map(pint_map);
    free_char_map(pchar_map);
}

