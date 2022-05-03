/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:57:56 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 20:28:18 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

int	wait_for_child(int pid, char **cmd_argv)
{
	int	result;
	int	status;

	if (cmd_argv == 0)
		return (-1);
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		result = WTERMSIG(status) + 128;
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
		int *ppipefd,
		t_arg_info *parg,
		char **cmd_argv
){
	pid_t		pid;
	ssize_t		rcnt;
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
	rcnt = read(ppipefd[READ_END], parg->cmd_path, sizeof(parg->cmd_path) - 1);
	if (rcnt < 0)
		return (-1);
	parg->cmd_path[rcnt - 1] = 0;
	return (0);
}
