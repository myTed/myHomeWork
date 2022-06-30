#include <stdio.h>

int	main(int argc, char *argv[])
{
	int idx = 0;
	while (argv[idx] != 0)
	{
		printf("argv[%d] = %s\n",idx, argv[idx]);
		if (argv[idx][0] == 0)
		{
			printf("빈 문자열있음");
			break;
		}
		idx++;
	}
	return (0);
}
