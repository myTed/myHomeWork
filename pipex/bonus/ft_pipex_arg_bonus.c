#include "ft_pipex_bonus.h"

int	get_cmd_argv_malloc(char *cmd_str, t_arg_info *parg)
{
	char **tmp;

	if ((cmd_str == 0) || (parg == 0))
		return (-1);
	tmp = ft_split(cmd_str, ' ');
	if (tmp == 0)
		return (-1);
	parg->cmd_argv = tmp;
	return (0);
}


int free_cmd_argv(t_arg_info *parg)
{
	int idx;

	if (parg == 0)
		return (-1);
	idx = 0;
	if (parg->cmd_argv != 0)
	{
		while(parg->cmd_argv[idx] != 0)
			free(parg->cmd_argv[idx++]);
		free(parg->cmd_argv);
		parg->cmd_argv = 0;
	}
	return (0);
}



