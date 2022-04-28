#include "ft_pipex_bonus.h"

int	get_fd_file(int cmd_idx, t_fd *ptfds, t_arg_info *parg)
{
	int 	fd;
	int		result;

	if ((ptfds == 0) || (parg == 0))
		return (-1);
	if (cmd_idx == 1)
	{
		result = open_infile(parg, &fd);
		if (result != 0)
			return (result);
		ptfds->in_file = fd;	
	}
	if(cmd_idx == parg->cmd_cnt)
	{
		result = open_outfile(parg, &fd);
		if (result != 0)
			return (result);
		ptfds->out_file = fd;
	}
	return (0);
}

int	close_unused_fd(int cmd_idx, t_fd *ptfds, t_arg_info *parg)
{
	int	idx;
	int	last_cmd_idx;
	int	pipe_cnt;

	if ((ptfds == 0) || (cmd_idx < 0) || (parg == 0))
		return (-1);
	last_cmd_idx = parg->cmd_cnt;
	pipe_cnt = parg->cmd_cnt - 1;
	if (cmd_idx == 1)
		if (close(ptfds->in_file) < 0)
			return (-1);
	if (cmd_idx == last_cmd_idx)
		if (close(ptfds->out_file) < 0)
			return (-1);
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


int	dup_stdin_stdout(int cmd_idx, t_fd *ptfds, t_arg_info *parg)
{
	int	last_cmd_idx;

	if ((ptfds == 0) || (parg == 0))
		return (-1);
	last_cmd_idx = parg->cmd_cnt;
	if (cmd_idx == 1)
	{
		if (dup2(ptfds->in_file, 0) < 0)
			return (-1);
		if (dup2(ptfds->ppipe[cmd_idx - 1][WRITE_END], 1) < 0)
			return (-1);
		return (0);
	}
	if (dup2(ptfds->ppipe[cmd_idx - 2][READ_END], 0) < 0)
		return (-1);
	if (cmd_idx == last_cmd_idx)
	{
		if (dup2(ptfds->out_file, 1) < 0)
			return (-1);
		return (0);
	}
	if (dup2(ptfds->ppipe[cmd_idx - 1][WRITE_END], 1) < 0)
		return (-1);
	return (0);
}

