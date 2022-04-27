#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"
#include "pipex_bonus.h"


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


int write_heredoc(int fd, t_arg_info *parg)
{
	int		read_cnt;
	char	buff[BUFF_SIZE];

	if (parg == 0)
		return (-1);
	while (1)
	{
		if (write(1, "heredoc> ", ft_strlen("heredoc> ")) < 0)
			return (-1);
		read_cnt = read(0, buff, sizeof(buff) - 1);
		if (read_cnt < 0)
			return (-1);
		if (ft_strncmp(buff, parg->here_info.limiter, read_cnt - 1) == 0)
			break;
		if (write(fd, buff, read_cnt) < 0)
			return (-1);
	}
	return (0);
}


int	open_outfile(t_arg_info *parg, int *pfd)
{
	int	fd;

	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (parg->here_info.is_here_doc)
		fd = open(parg->out_filename, O_CREAT | O_WRONLY | O_APPEND, 00600);
	else
		fd = open(parg->out_filename, O_CREAT | O_WRONLY | O_TRUNC, 00600);
	if (fd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->out_filename);
		return (1);
	}
	*pfd = fd;
	return (0);
}


int	make_heredoc_file(t_arg_info *parg)
{
	int	fd;

	if (parg == 0)
		return (-1);
	fd = open(parg->in_filename, O_CREAT | O_RDWR | O_TRUNC, 00600);
	if (fd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	if (write_heredoc(fd, parg) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}


int	open_infile_for_read(t_arg_info *parg, int *pfd)
{
	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (access(parg->in_filename, R_OK) == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	*pfd = open(parg->in_filename, O_RDONLY);
	if (*pfd == -1)
	{
		write(2, "bash: ", ft_strlen("bash: "));
		perror(parg->in_filename);
		return (1);
	}
	if (parg->here_info.is_here_doc)
	{
		if (unlink(parg->in_filename) < 0)
		{
			close(*pfd);
			return (1);
		}
	}
	return (0);
}


int	open_infile(t_arg_info *parg, int *pfd)
{
	int	result;

	if ((parg == 0) || (pfd == 0))
		return (-1);
	if (parg->here_info.is_here_doc)
	{
		result = make_heredoc_file(parg);
		if (result != 0)
			return (result);
	}
	return (open_infile_for_read(parg, pfd));
}


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


int	exec_cmd(int cmd_idx, char **argv, t_fd *ptfds, t_arg_info *parg)
{
	int	result;

	if ((ptfds == 0) || (parg == 0))
		return (-1);
	result = get_fd_file(cmd_idx, ptfds, parg);
	if (result != 0)
		return (result);
	if (get_cmd_argv_malloc(
			argv[parg->argc - (parg->cmd_cnt + 2) + cmd_idx], 
			parg) < 0)
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
	while (waitpid(-1, &status, 0) > 0);
	return (result);
}


int	exec_cmd_loop(
		char 		**argv,
		t_arg_info 	*parg,
		t_fd 		*ptfds
){
	int			cmd_idx;
	int			last_cmd_pid;
	pid_t		pid;

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


int	is_valid_argc(int argc, char **argv, char *here_doc)
{
	char	*invalid_here_str;
	char	*invalid_cmd_str;

	invalid_here_str = "Usage: Program here_doc LIMITER cmd1 cmd2 outfile\n";
	invalid_cmd_str = "Usage: Program infile cmd1 cmd2 outfile\n";
	if ((argv == 0) || (here_doc == 0))
		return (-1);
	if (ft_strncmp(argv[1], here_doc, ft_strlen(here_doc) + 1) == 0)
	{
		if (argc < 6)
		{
			write(2, invalid_here_str, ft_strlen(invalid_here_str));
			return (-1);
		}
	}
	else
	{
		if (argc < 5)
		{
			write(2, invalid_cmd_str, ft_strlen(invalid_cmd_str));
			return (-1);
		}
	}
	return (0);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_fd 		fds;
	t_arg_info	arg_inform;
	int			last_cmd_status;
	
	if (is_valid_argc(argc, argv, "here_doc") < 0)
		return (-1);
	if (fill_arg_inform(argc, argv, envp, &arg_inform) != 0)
		return (-1);
	if (malloc_pipe(argc, &fds, &arg_inform) < 0)
		return (-1);
	last_cmd_status = exec_cmd_loop(argv, &arg_inform, &fds);
	if (free_pipe(&fds) < 0)
		return (-1);
	return (last_cmd_status);
}
