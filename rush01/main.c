#include <stdio.h>


void swap(int *a,int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}




void recursive(int *arr,int start_index, int size)
{

	if( start_index == size - 1)
	{
		for(int i=0; i<size; i++)
		{
			printf("%d ",arr[i]);
		}
		printf("\n");
		return ;		
	}


	for(int i = start_index; i < size; i++)
	{
		swap(&arr[start_index], &arr[i]);
		recursive( arr, start_index + 1, size);
		swap(&arr[start_index], &arr[i]);
	}
		
}


void make_arr_list(int *arr, int size)
{

	recursive(arr, 0, size);
}



int	main(void)
{

	int arr[] = {1, 2, 4};

	make_arr_list(arr, sizeof(arr)/sizeof(arr[0]));
	


	return (0);
}
