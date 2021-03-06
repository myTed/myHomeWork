/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_exec_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:15:32 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 19:26:23 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	exec_cmd(int cmd_idx, char **argv, t_fd *ptfds, t_arg_info *parg)
{
	int	result;

	if ((ptfds == 0) || (parg == 0))
		return (-1);
	result = get_fd_file(cmd_idx, ptfds, parg);
	if (result != 0)
		return (result);
	if (get_cmd_argv_malloc(
			argv[parg->argc - (parg->cmd_cnt + 2) + cmd_idx], parg) < 0)
		return (-1);
	result = get_cmd_path(parg);
	if (result != 0)
	{
		free_cmd_argv(parg);
		return (result);
	}
	if (dup_stdin_stdout(cmd_idx, ptfds, parg) < 0)
		return (-1);
	if (close_unused_fd(cmd_idx, ptfds, parg) < 0)
		return (-1);
	if (execve(parg->cmd_path, parg->cmd_argv, parg->envp) < 0)
		free_cmd_argv(parg);
	return (-1);
}

int	wait_for_children(int last_cmd_pid)
{
	int	result;
	int	status;

	if (waitpid(last_cmd_pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		result = WTERMSIG(status) + 128;
	while (
		waitpid(-1, &status, 0) > 0);
	return (result);
}

int	close_all_fd(t_fd *ptfds, t_arg_info *parg)
{
	int	pipe_cnt;
	int	idx;

	if ((ptfds == 0) || (parg == 0))
		return (-1);
	pipe_cnt = parg->cmd_cnt - 1;
	idx = 0;
	while (idx < pipe_cnt)
	{
		if (close(ptfds->ppipe[idx][READ_END]) < 0)
			return (-1);
		if (close(ptfds->ppipe[idx][WRITE_END]) < 0)
			return (-1);
		idx++;
	}
	return (0);
}

int	exec_cmd_loop(
		char **argv,
		t_arg_info *parg,
		t_fd *ptfds
){
	int		cmd_idx;
	int		last_cmd_pid;
	pid_t	pid;

	cmd_idx = 1;
	while (cmd_idx < parg->cmd_cnt + 1)
	{
		pid = fork();
		if (cmd_idx == parg->cmd_cnt)
			last_cmd_pid = pid;
		if (pid < 0)
		{
			perror("fork error");
			return (-1);
		}
		else if (pid == 0)
			return (exec_cmd(cmd_idx, argv, ptfds, parg));
		else
			cmd_idx++;
	}
	if (close_all_fd(ptfds, parg) < 0)
		return (-1);
	return (wait_for_children(last_cmd_pid));
}
