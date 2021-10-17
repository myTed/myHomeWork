typedef struct {
	int* sample_buffer;
	int sample_buffer_size;
	int* not_zero_buffer;
	int not_zero_buffer_size;
} buffer_info;


typedef struct {
	int* start_address;
	int rows;
	int cols;
	int index;
}matrix_buffer_info;


buffer_info	make_sample_array_for_number_of_case(int* puzzle_map_row, int(*hint_map)[4], int row_size, int col_size);
matrix_buffer_info make_case_array_list(int* sample_array, int sample_array_size);
int get_factorial(int n);
matrix_buffer_info make_final_array_list_for_check(int* puzzle_map_row, matrix_buffer_info* pcase_array, int puzzle_col_size);
void fill_final_array_from_case_array(matrix_buffer_info* dest_array, matrix_buffer_info* src_array);
void recursive_array(int* arr, int start_index, int size, matrix_buffer_info* pcase_array);
void fill_case_array(int* case_array, int* sample_array, int sample_array_size);
void ft_swap(int* a, int* b);
void fill_sample_buffer(buffer_info* buffer_info, int max_value);
int* make_dummy_sample_buffer(int sample_row_size);
void fill_not_zero_buffer(int* puzzle_map_row, int* not_zero_buffer, int row_size);
int get_count_not_zero_from_rowmap(int* map_row, int col_size);
int get_max_value_from_hint(int(*map)[4], int row_count, int col_count);
int get_min_value_from_hint(int(*map)[4], int row_count, int col_count);
