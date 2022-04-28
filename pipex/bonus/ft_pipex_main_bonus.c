#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_pipex_bonus.h"
#include "ft_pipex_utils_gnl_bonus.h"

int	malloc_pipe(int argc, t_fd *ptfds, t_arg_info *parg)
{
	int	(*tmp)[2];
	int	idx;
	int	pipe_cnt;

	if ((argc < 5) || (ptfds == 0) || (parg == 0))
		return (-1);
	pipe_cnt = parg->cmd_cnt - 1;
	tmp = malloc(sizeof(*(ptfds->ppipe)) * (pipe_cnt));
	if (tmp == 0)
		return (-1);
	ptfds->ppipe = tmp;
	idx = 0;
	while (idx < pipe_cnt)
		if (pipe(ptfds->ppipe[idx++]) < 0)
			return (-1);
	return (0);
}

int free_pipe(t_fd *ptfds)
{
	if (ptfds == 0)
		return (-1);
	free(ptfds->ppipe);
	return (0);
}

int	fill_arg_inform(int argc, char **argv, char **envp, t_arg_info *parg)
{
	if ((argc < 1) || (argv == 0) || (envp == 0) || (parg == 0))
		return (-1);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") + 1) == 0)
	{
		parg->here_info.limiter = argv[2];
		parg->here_info.is_here_doc = 1;
		parg->in_filename = "tmp_doc";
		parg->cmd_cnt = argc - 4;
	}
	else
	{
		parg->here_info.limiter = 0;
		parg->here_info.is_here_doc = 0;
		parg->in_filename = argv[1];
		parg->cmd_cnt = argc - 3;
	}
	parg->argc = argc;
	parg->envp = envp;
	parg->out_filename = argv[argc - 1];
	parg->cmd_argv = 0;
	parg->cmd_path[0] = 0;
	return (0);
}

int	is_valid_argc(int argc, char **argv, char *here_doc)
{
	char	*invalid_here_str;
	char	*invalid_cmd_str;

	invalid_here_str = "Usage: Program here_doc LIMITER cmd1 cmd2 outfile\n";
	invalid_cmd_str = "Usage: Program infile cmd1 cmd2 outfile\n";
	if ((argv == 0) || (here_doc == 0))
		return (-1);
	if (argv[1] != 0)
	{
		if(ft_strncmp(argv[1], here_doc, ft_strlen(here_doc) + 1) == 0)
		{
			if (argc < 6)
			{
				write(2, invalid_here_str, ft_strlen(invalid_here_str));
				return (-1);
			}
			return (0);
		}
	}
	if (argc < 5)
	{
		write(2, invalid_cmd_str, ft_strlen(invalid_cmd_str));
		return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_fd 		fds;
	t_arg_info	arg_inform;
	int			last_cmd_status;
	
	if (is_valid_argc(argc, argv, "here_doc") < 0)
		return (1);
	if (fill_arg_inform(argc, argv, envp, &arg_inform) != 0)
		return (-1);
	if (malloc_pipe(argc, &fds, &arg_inform) < 0)
		return (-1);
	last_cmd_status = exec_cmd_loop(argv, &arg_inform, &fds);
	if (free_pipe(&fds) < 0)
		return (-1);
	return (last_cmd_status);
}
