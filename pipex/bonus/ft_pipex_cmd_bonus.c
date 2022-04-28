#include "ft_pipex_bonus.h"

int	wait_for_child(int pid, char **cmd_argv)
{
	int	result;
	int	status;

	if (cmd_argv == 0)
		return (-1);
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status))
		result =  WEXITSTATUS(status);
	if (result != 0)
	{
		write(2, "command not found : ", ft_strlen("command not found : "));
		write(2, cmd_argv[1], ft_strlen(cmd_argv[1]));
		write(2, "\n", 1);
		return (127);
	}
	return (result);
}

int	get_result_which_cmd(
		int			*ppipefd,
		t_arg_info 	*parg,
		char 		**cmd_argv
){
	pid_t		pid;
	ssize_t		read_cnt;
	int			result;

	if ((ppipefd == 0) || (parg == 0) || (cmd_argv == 0))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (dup2(ppipefd[WRITE_END], 1) < 0)
			return (-1);
		execve("/usr/bin/which", cmd_argv, parg->envp);
		return (-1);
	}
	parg->cmd_path[0] = 0;
	result = wait_for_child(pid, cmd_argv);
	if (result != 0)
		return (result);
	read_cnt = read(ppipefd[READ_END], parg->cmd_path, sizeof(parg->cmd_path) - 1);
	if (read_cnt < 0)
		return (-1);
	parg->cmd_path[read_cnt - 1] = 0;
	return (0);
}


int	get_cmd_path(t_arg_info *parg)
{
	int		pipefds[2];
	char	*which_argv[3];
	int		result;

	if ((parg == 0))
		return (-1);
	if (pipe(pipefds) < 0)
		return (-1);
	which_argv[0] = "which";
	which_argv[1] = parg->cmd_argv[0];
	which_argv[2] = 0;
	result = get_result_which_cmd(pipefds, parg, which_argv);
	close(pipefds[READ_END]);
	close(pipefds[WRITE_END]);
	return (result);
}


