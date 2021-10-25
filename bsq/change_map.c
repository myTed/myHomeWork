#include "change_map.h"
#include "cal_square.h"
#include "mark.h"

int **make_int_map(Mark *pmark)
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


void fill_char_map_to_int_map(char **pchar_map,Mark *pmark,int **pint_map)
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
			if(pchar_map[row_idx][col_idx] == pmark->ch[EMPTY_INDEX])
				pint_map[row_idx][col_idx] = 1;
			if(pchar_map[row_idx][col_idx] == pmark->ch[OBSTACLE_INDEX])
				pint_map[row_idx][col_idx] = 0;
			col_idx++;
		}
		row_idx++;
	}
}


void print_map(Mark *pmark,int **pint_map)
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
			printf("%d ",pint_map[row_idx][col_idx]);
			col_idx++;
		}
		row_idx++;
		printf("\n");
	}
}


char **test_make_char_map(Mark *pmark)
{
	char **pchar_map;
	int row_idx;

	pchar_map = NULL;
	row_idx = 0;
	pchar_map = (char**)malloc(sizeof(char*) * (pmark->rows + 1));
	if (pchar_map == NULL)
		return NULL;

	while (row_idx < pmark->rows)
	{
		pchar_map[row_idx] = (char*)malloc(sizeof(char) * (pmark->cols));
		row_idx++;
	}
	pchar_map[row_idx] = 0;

	return pchar_map;
}

void test_copy_map(char *pchar_map, char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != 0)
	{
		pchar_map[idx] = str[idx];
		idx++;
	}
}

void test_fill_char_map(Mark *pmark, char **pchar_map)
{

	char *str1[9];

	int	row_idx;
	int str_idx;

	row_idx = 0;
	str_idx = 0;
	str1[0] = "...........................";
	str1[1] = "....o......................";
	str1[2] = "............o..............";
	str1[3] = "...........................";
	str1[4] = "....o......................";
	str1[5] = "...............o...........";
	str1[6] = "...........................";
	str1[7] = "......o..............o.....";
	str1[8] = "..o.......o................";

	while (row_idx < pmark->rows)
	{
		test_copy_map(pchar_map[row_idx], str1[str_idx]);
		row_idx++;
		str_idx++;
	}
}

void test_print_char_map(Mark *pmark,char **pchar_map)
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
			printf("%c ",pchar_map[row_idx][col_idx]);
			col_idx++;
		}
		row_idx++;
		printf("\n");
	}
}



void print_max_square(Mark *pmark, char **pchar_map, t_coordinate *pmax_square)
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
			{
				write(1, &pmark->ch[OCCUPY_INDEX], 1);
				write(1, " ", 1);
			}
			else
			{
				write(1, &pchar_map[row_idx][col_idx], 1);
				write(1, " ", 1);
			}
			col_idx++;
		}
		write(1,"\n", 1);
		row_idx++;
	}
}



int	main(void)
{

	Mark mark;
	t_coordinate max_square;
	int	max_value;

	int **pint_map;
	char **pchar_map;

	mark.rows = 9;
	mark.cols = 27;
	mark.ch[0] = '.';
	mark.ch[1] = 'o';
	mark.ch[2] = 'x';
	pint_map = NULL;
	pchar_map = NULL;

	pchar_map = test_make_char_map(&mark);
	if (pchar_map == NULL)
	{
		printf("Can't make char map\n");
		return -1;
	}
	
	test_fill_char_map(&mark,pchar_map);
	test_print_char_map(&mark,pchar_map);


	printf("\n\n");	
	
	pint_map = make_int_map(&mark);
	if (pint_map == NULL)
		return (-1);
	
	fill_char_map_to_int_map(pchar_map,&mark,pint_map);
	print_map(&mark,pint_map);

	printf("\n\n");
	
	max_value = cal_square(&mark, pint_map);
	get_coordinate_max_square(&mark, pint_map, max_value, &max_square);
	
	print_map(&mark,pint_map);

	printf("\n\n");
	print_max_square(&mark, pchar_map, &max_square);
	

	free(pchar_map);
	free(pint_map);
	return (0);
}

