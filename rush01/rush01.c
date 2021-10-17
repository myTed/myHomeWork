


#include <stdio.h>
#include "comon.h"
#include <stdlib.h>

#define LOWS 4
#define COLS 4


int get_min_value_from_hint(int (*map)[4], int row_count, int col_count)
{
	int	row;
	int col;
	int min_value;

	row = 0;
	col = 0;
	min_value = 1;
	while (row < row_count)
	{
		col = 0;
		while (col < col_count)
		{
			if (map[row][col] < min_value)
			{
				min_value = map[row][col];
			}
			col++;
		}
		row++;
	}
	return min_value;
}


int get_max_value_from_hint(int (*map)[4], int row_count, int col_count)
{
	int	row;
	int col;
	int maxim_value;

	row = 0;
	col = 0;
	maxim_value = 1;
	while (row < row_count)
	{
		col = 0;
		while (col < col_count)
		{
			if (map[row][col] > maxim_value)
			{
				maxim_value = map[row][col];
			}
			col++;
		}
		row++;
	}
	return maxim_value;
}



int get_count_not_zero_from_rowmap(int *map_row, int col_size)
{
	int	col;
	int	count;

	col = 0;
	count = 0;	

	while (col < col_size)
	{
		if (map_row[col] != 0) 
		{
			count++;
		}
		col++;
	}
	return count;
}



void fill_not_zero_buffer(int* puzzle_map_row, int* not_zero_buffer, int row_size)
{
	int idx;
	int fill_index;
	int value;

	idx = 0;
	fill_index = 0;
	while (idx < row_size)
	{
		value = puzzle_map_row[idx];
		if (value != 0)
		{
			not_zero_buffer[fill_index++] = value;
		}
		idx++;
	}
}


int* make_dummy_sample_buffer(int sample_row_size)
{
	int *sample_buffer;

	sample_buffer = NULL;
	sample_buffer = malloc(sizeof(int) * sample_row_size);
	if (sample_buffer == NULL)
	{
		return NULL;
	}
	return sample_buffer;
}

void fill_sample_buffer(buffer_info *buffer_info, int max_value)
{
	int idx;
	int *tmp_buffer;
	int sample_index;

	idx = 0;
	tmp_buffer = NULL;
	sample_index = 0;
	tmp_buffer = malloc(sizeof(int) * max_value);
	while (idx < max_value)
	{
		tmp_buffer[idx] = idx + 1;
		idx++;
	}
	idx = 0;
	while (idx < buffer_info->not_zero_buffer_size)
	{
		tmp_buffer[buffer_info->not_zero_buffer[idx++] - 1] = 0;
	}
	idx = 0;
	while (idx < max_value)
	{
		if (tmp_buffer[idx] != 0)
		{
			buffer_info->sample_buffer[sample_index++] = tmp_buffer[idx];
		}
		idx++;
	}
	free(tmp_buffer);
}



void ft_swap(int* a, int* b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}


void fill_case_array(int* case_array, int* sample_array, int sample_array_size)
{
	int idx;
	
	idx = 0;
	while (idx < sample_array_size)
	{
		case_array[idx] = sample_array[idx];
		idx++;
	}
}




void recursive_array(int *arr, int start_index, int size, matrix_buffer_info*pcase_array)
{
	int i;
	int idx;

	idx = pcase_array->index;
	if (start_index == size - 1)
	{
		fill_case_array( &(pcase_array->start_address[idx]), arr, size );
		pcase_array->index += size;
	}
	i = start_index;
	while ( i < size)
	{
		ft_swap(&arr[start_index], &arr[i]);
		recursive_array(arr, start_index + 1, size, pcase_array);
		ft_swap(&arr[start_index], &arr[i]);
		i++;
	}
}



void fill_final_array_from_case_array(matrix_buffer_info*dest_array, matrix_buffer_info* src_array)
{
	int idx_row;
	int idx_col;
	int src_idx;
	int dest_idx;

	idx_row = 0;
	idx_col = 0;
	src_idx = 0;
	dest_idx = 0;	
	while (idx_row < dest_array->rows)
	{
		idx_col = 0;
		while (idx_col < dest_array->cols)
		{
			if (dest_array->start_address[dest_idx] == 0)
			{
				dest_array->start_address[dest_idx] = src_array->start_address[src_idx++];
			}
			dest_idx++;
			idx_col++;
		}
		idx_row++;
	}
}

matrix_buffer_info make_final_array_list_for_check(int *puzzle_map_row, matrix_buffer_info* pcase_array, int puzzle_col_size)
{
	matrix_buffer_info final_case_array;
	int final_case_idx;
	int puzzle_idx;

	final_case_array.start_address = malloc( sizeof(int) * pcase_array->rows * puzzle_col_size);
	final_case_idx = 0;
	final_case_array.rows = pcase_array->rows;
	final_case_array.cols = puzzle_col_size;
	puzzle_idx = 0;
	while (final_case_idx < final_case_array.rows * final_case_array.cols)
	{
		puzzle_idx = 0;
		while (puzzle_idx < puzzle_col_size)
		{
			final_case_array.start_address[final_case_idx] = puzzle_map_row[puzzle_idx];
			puzzle_idx++;
			final_case_idx++;
		}
	}
	fill_final_array_from_case_array(&final_case_array, pcase_array);
	free(pcase_array->start_address);

	return final_case_array;
}



int get_factorial(int n)
{
	if (n <= 1) return 1;
	return n * get_factorial(n - 1);
}

matrix_buffer_info make_case_array_list(int *sample_array, int sample_array_size)
{
	matrix_buffer_info s_case_array;
	s_case_array.cols = sample_array_size;
	s_case_array.rows = get_factorial(sample_array_size);
	s_case_array.start_address = (int*)malloc(sizeof(int) * (s_case_array.rows * (sample_array_size)));
	s_case_array.index = 0;

	recursive_array(sample_array, 0, sample_array_size, &s_case_array);

	return s_case_array;
}



buffer_info	make_sample_array_for_number_of_case(int *puzzle_map_row, int (*hint_map)[4], int row_size, int col_size)
{
	int not_zero_count;
	int max_value;
	int min_value;


	buffer_info s_buffer_info;

	not_zero_count = get_count_not_zero_from_rowmap(puzzle_map_row, col_size);
	if (not_zero_count == 0)
	{
		s_buffer_info.not_zero_buffer = NULL;
		return s_buffer_info;
	}

	s_buffer_info.not_zero_buffer = (int*)malloc(sizeof(int) * not_zero_count);
	s_buffer_info.not_zero_buffer_size = not_zero_count;
	fill_not_zero_buffer( puzzle_map_row, s_buffer_info.not_zero_buffer, row_size);

	max_value = get_max_value_from_hint(hint_map, row_size, col_size);
	min_value = get_min_value_from_hint(hint_map, row_size, col_size);

	s_buffer_info.sample_buffer_size = max_value - not_zero_count;
	s_buffer_info.sample_buffer = make_dummy_sample_buffer(s_buffer_info.sample_buffer_size);

	fill_sample_buffer(&s_buffer_info, max_value);
	free(s_buffer_info.not_zero_buffer);

	return s_buffer_info;
}



int	main(int argc, char *argv[])
{
	int puzzle_map[4][4] = {
		{0, 1, 2, 0},
		{0, 3, 0, 0},
		{0, 4, 1, 0},
		{1, 2, 3, 4}
	};

	int hint_map[4][4] = { 
			{4, 3, 2, 1}, 
			{1, 2, 2, 2}, 
			{4, 3, 2, 1}, 
			{1, 2, 2, 2} 
	};

	
	//int max_number;
	//int min_number;


	//max_number = get_max_value_from_hint(hint_map, 4, 4);
	//min_number = get_min_value_from_hint(hint_map, 4, 4);

	buffer_info buffer1;
	buffer_info buffer2;
	//buffer_info buffer3;
	buffer_info buffer4;
	matrix_buffer_info case_array1;
	matrix_buffer_info case_array2;
	matrix_buffer_info final_case_array1;
	//buffer1 = make_sample_array_for_number_of_case(puzzle_map[0], hint_map, 4, 4);
	

	buffer2 = make_sample_array_for_number_of_case(puzzle_map[0], hint_map, 4, 4);
	if (buffer2.not_zero_buffer != NULL)
	{
		case_array2 = make_case_array_list(buffer2.sample_buffer, buffer2.sample_buffer_size);
		final_case_array1 = make_final_array_list_for_check(puzzle_map[0], &case_array2, 4);
	}


	return (0);
}


