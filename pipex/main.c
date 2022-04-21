/*
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

int get_pathname(
		char *in_filename, 
		char *out_path_name, 
		size_t path_cnt
){
	int		pid;
	int		pipefd[2];
	int		std_out;
	int		old_std_out;
	ssize_t	read_cnt;
	extern	char **environ;
	int		status;

	if (in_filename == 0)
		return (-1);
	if (pipe(pipefd) < 0)
		exit(1);
	old_std_out = dup(1);
	if (old_std_out < 0)
		exit(1);
	std_out = dup2(pipefd[1], 1);
	if (std_out == -1)
		exit(1);
	pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	else if(pid == 0) {
		char * which_argv[] = { "which", in_filename, NULL };
		execve("/usr/bin/which", which_argv, environ);
		perror("execv error");
		exit(1);
	}
	else {
		if (waitpid(pid, &status, 0) < 0)
			exit(1);
		if (WIFEXITED(status) && WEXITSTATUS(status)) {
			exit(1);
		}
		read_cnt = read(pipefd[0], out_path_name, path_cnt - 1);
		out_path_name[read_cnt - 1] = 0;
		close(pipefd[1]);
		close(pipefd[0]);
		if (dup2(old_std_out, 1) < 0)
			exit(1);
		close(old_std_out);
	}
	return (0);
}


int is_access_file(char *file_name)
{
	if (access(file_name, R_OK) == -1) {
		perror("Not Access");
		return (-1);
	}
	return (0);
}

int	is_access_cmd(char *cmd_name, char *path_cmd)
{
	char	**cmd_argv;
	int		result;
	int		i;

	result = -1;
	cmd_argv = ft_split(cmd_name, ' ');
	if (cmd_argv == 0)
		return (result);
	if (get_path_cmd(cmd_argv[0], path_cmd) < 0)
		return (result);
	while (i = 0; cmd_argv[i] != 0; i++)
		free(cmd_argv[i]);
	free(cmd_argv);
	return (0);
}


int	open_file(char *file_name)
{
	int	fd;

	if (is_access_file(file_name) < 0)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}


int redirection_fd(int old_fd, int new_fd)
{
	change_fd(fd, 0);
	fd_zero = dup2(fd, 0);
	if (fd_zero == -1) {
		perror("Dup2 Error");
		return (-1);
	}
	close(fd);
	if (pipe(pipefd) == -1) {
		perror("pipe Error");
		return (-1);
	}
	fd_one = dup2(pipefd[1], 1);
	if (fd_one == -1) {
		perror("Dup2 Error");
		return (-1);
	}
	close(pipefd[1]);
}


int	
//1. file open
//2. file open descriptor -> stdin
//3. fork
//4. exec
//5. 

int	change_fd(int *pold_fd, int new_fd)
{
	int	temp_fd;

	if (pold_fd == 0)
		return (-1);
	temp_fd = dup2(fd, new_fd);
	if (temp_fd == -1) {
		perror("dup2 Error");
		return (-1);
	}
	close(*pold_fd);
	return (0);
}


int	is_get_path_cmd(char *find_cmd, char *path_cmd)
{
	int				old_fd_output;
	int				pipefd[2];
	extern char		**environ;
	ssize_t			read_cnt;
	int				status;

	// ready pipe
	old_fd_output = dup(1);
	if (old_fd_output == -1)
		return (-1);
	// create pipe
	if (pipe(pipefd) < 0)
		exit(1);
	if (dup2(1, pipefd[1]) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0) {
		execve("/bin/which", find_cmd, environ);
		perror("faild to exec");
		exit(1);
	}
	if (waitpid(pid, &status, NULL) < 0)
		exit(1);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (-1);
	read_cnt = read(pipefd[0], path_cmd, path_cnt);
	if (read_cnt < 0)
		return (-1);
	path_cmd[read_cnt - 1] = 0;
	close(pipefd[0]);
	close(pipefd[1]);
	if (dup2(1, old_fd_output) < 0)
		return (-1);
	return (0);
}
*/

#define MAX_PATH_LEN	128
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"


typedef struct s_resource{
	char	*filename1;
	char	*filename2;
	char	**cmd_argv;
	char 	cmd_path[MAX_PATH_LEN];
} t_arg_info;

typedef struct s_fd {
	int		file1;
	int		file2;
	int		pipe1fd[2];
	int		pipe2fd[2];
} t_fd;

int open_resources(t_arg_info *parg, t_fd *pfds)
{
	int	fd;

	if (access(parg->filename1, R_OK) == -1)
	{
		perror("Not Access file1");
		return (-1);
	}
	fd = open(parg->filename1, O_RDONLY);
	if (fd == -1)
		return (-1);
	pfds->file1 = fd;
	fd = open(parg->filename2, O_CREAT | O_WRONLY | O_TRUNC, 00600);
	if (fd == -1)
	{
		perror("file2 open error");
		return (-1);
	}
	pfds->file2 = fd;
	if (pipe(pfds->pipe1fd) < 0)
		return (-1);
	if (pipe(pfds->pipe2fd) < 0)
		return (-1);
	return (0);
}

int	fill_arg_inform(int argc, char **argv, t_arg_info *parg)
{
	if ((argc < 1) || (argv == 0) || (parg == 0))
		return (-1);
	parg->filename1 = argv[1];
	parg->filename2 = argv[argc - 1];
	parg->cmd_argv = 0;
	parg->cmd_path[0] = 0;
	return (0);
}
/*
int	close_resources(t_fd *pfds)
{	
	if (close(pfds->file1) < 0)
		return (-1);
	if (close(pfds->file2) < 0)
		return (-1);
	if (close(pfds->pipe1fd[0]) < 0)
		return (-1);
	if (close(pfds->pipe1fd[1]) < 0)
		return (-1);
	if (close(pfds->pipe2fd[0]) < 0)
		return (-1);
	if (close(pfds->pipe2fd[1]) < 0)
		return (-1);
	return (0);
}
*/

int	change_stdin_stdout_parent(
		int argc, 
		int cmd_idx,
		t_fd *pfds
){
	if (pfds == 0)
		return (-1);
	if (cmd_idx == 1)
	{
		if (close(pfds->pipe1fd[1]) < 0)
			return (-1);
		if (close(pfds->file1) < 0)
			return (-1);
		return (0);
	}
	else if (cmd_idx == argc - 3)
	{
		if (close(pfds->file2) < 0)
			return (-1);
	}
	else
	{
		if (cmd_idx % 2 == 0)
		{
			if (close(pfds->pipe2fd[1]) < 0)
				return (-1);
			if (close(pfds->pipe1fd[0]) < 0)
				return (-1);
			if (pipe(pfds->pipe1fd) < 0)
				return (-1);		
		}
		else
		{
			if (close(pfds->pipe1fd[1]) < 0)
				return (-1);
			if (close(pfds->pipe2fd[0]) < 0)
				return (-1);
			if (pipe(pfds->pipe2fd) < 0)
				return (-1);
		}
	}
	return (0);
}


int change_stdin_stdout_child(
		int argc,
		int cmd_idx,
		t_fd *pfds
){
	if (pfds == 0)
		return (-1);
	if (cmd_idx == 1)
	{
		if (dup2(pfds->file1, 0) < 0)
			return (-1);
		if (dup2(pfds->pipe1fd[1], 1) < 0)
			return (-1);
	}
	else
	{
		if (cmd_idx % 2 == 0)
		{
			if (dup2(pfds->pipe1fd[0], 0) < 0)
				return (-1);
			if (dup2(pfds->pipe2fd[1], 1) < 0)
				return (-1);
		}
		else
		{
			if (dup2(pfds->pipe2fd[0], 0) < 0)
				return (-1);
			if (dup2(pfds->pipe1fd[1], 1) < 0)
				return (-1);
		}
	}
	if (cmd_idx == argc - 3)
		if (dup2(pfds->file2, 1) < 0)
			return (-1);
	/*
	if (close_resources(pfds) < 0)
		return (-1);
	*/
	return (0);
}


int	get_result_which_cmd(
		int			*ppipefd,
		t_arg_info 	*parg,
		char 		**cmd_argv
){
	pid_t		pid;
	extern char	**environ;
	ssize_t		read_cnt;
	int			status;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (dup2(ppipefd[1], 1) < 0)
			return (-1);
		execve("/usr/bin/which", cmd_argv, environ);
		return (-1);
	}
	parg->cmd_path[0] = 0;
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (-1);
	read_cnt = read(ppipefd[0], parg->cmd_path, sizeof(parg->cmd_path) - 1);
	if (read_cnt < 0)
		return (-1);
	parg->cmd_path[read_cnt - 1] = 0;
	return (0);
}

int	get_path_cmd(t_fd *pfds, t_arg_info *parg)
{
	int		pipefds[2];
	char	*which_argv[3];

	if ((pfds == 0) || (parg == 0))
		return (-1);
	if (pipe(pipefds) < 0)
		return (-1);
	which_argv[0] = "which";
	which_argv[1] = parg->cmd_argv[0];
	which_argv[2] = 0;
	if (get_result_which_cmd(pipefds, parg, which_argv) < 0)
		return (-1);
	close(pipefds[0]);
	close(pipefds[1]);
	return (0);
}

int	get_argv_cmd(char *cmd_str, t_arg_info *parg)
{
	char	**tmp;
	int		idx;

	tmp = ft_split(cmd_str, ' ');
	if (tmp == 0)
		return (-1);
	if (parg->cmd_argv != 0)
	{
		idx = 0;
		while (parg->cmd_argv[idx] != 0)
			free(parg->cmd_argv[idx++]);
		free(parg->cmd_argv);
	}
	parg->cmd_argv = tmp;
	return (0);
}

int	execute_cmd(int argc, int cmd_idx, t_fd *pfd, t_arg_info *parg)
{
	pid_t		pid;
	extern char	**environ;
	int			status;
	//char		buff[128];
	//ssize_t		read_cnt;
	/*
	size_t		loop_cnt;
	size_t		loop_cnt2;
	*/
	pid = fork();
	fprintf(stderr, "%d\n", pid);
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (change_stdin_stdout_child(argc, cmd_idx, pfd) < 0)
			return (-1);
		execve(parg->cmd_path, parg->cmd_argv, environ);
		return (-1);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (-1);
	if (WIFEXITED(status) && WEXITSTATUS(status))
		return (-1);
	if (change_stdin_stdout_parent(argc, cmd_idx, pfd) < 0)
		return (-1);
	/*
	if (cmd_idx == 1)
	{
		read_cnt = read(pfd->pipe1fd[0], buff, sizeof(buff) - 1);
		buff[read_cnt] = 0;
		fprintf(stderr, "%s\n", buff);
	}
	*/
	return (0);
}

int	main(int argc, char *argv[])
{
	int 		idx;
	t_arg_info	arg_inform;
	t_fd		fds;
	//char		buff[128];
	//ssize_t		read_cnt;

	if (argc < 5)
	{
		printf("Usage : Program file1 cmd1 cmd2 file2\n");
		return (-1);
	}
	if (fill_arg_inform(argc, argv, &arg_inform) < 0)
		return (-1);
	if (open_resources(&arg_inform, &fds) < 0)
		return (-1);
	idx = 1;
	while (idx < argc - 2)
	{
		if (get_argv_cmd(argv[idx + 1], &arg_inform) < 0)
			return (-1);
		if (get_path_cmd(&fds, &arg_inform) < 0)
			return (-1);
		if (execute_cmd(argc, idx, &fds, &arg_inform) < 0)
			return (-1);
		idx++;
	}
	return (0);
}





/*
int	main(int argc, char *argv[])
{
	
	int		fd;
	int		fd_zero;
	int		fd_one;
	pid_t	pid;
	extern	char **environ;
	int		pipefd[2];
	
	char	path_name[128];
	char	**cmd_argv;
	int		idx;
	char	*path_file1;
	char	*path_file2;
	char	*path_cmd1;
	char	*path_cmd2;

	if (argc != 5) {
		printf("Usage : Program file1 cmd1 cmd2 file2\n");
		printf("%d\n", argc);
		return (0);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork error\n");
		return (-1);
	}
	else if (pid == 0) { // 자식 프로세스
		char *newargv[] = {argv[2] , NULL};
		if (execve(argv[2], newargv, environ) == -1) {
			perror("Exec Error: ");
			return (-1);
		}
		printf("asjkdlfjklasjdlkfj----------------\n");
	}
	else { // 부모 프로세스
		if (waitpid(pid, NULL, 0) < 0) {
			perror("Wait error");
			return (-1);
		}
		close(fd_zero);
		fd_zero = dup2(pipefd[0], 0);
		if (fd_zero == -1) {
			perror("Dup2 Error");
			return (-1);
		}
		if (access(argv[4], W_OK) == -1) {
			perror("Not Access");
			return (-1);
		}
		fd = open(argv[4], O_WRONLY);
		if (fd == -1) {
			perror("open Error");
			return (-1);
		}
		close(fd_one);
		fd_one = dup2(fd, 1);
		if (fd_one == -1) {
			perror("dup2 Error");
			return (-1);
		}
		pid = fork();
		if (pid == -1) {
			perror("fork error2\n");
			return (-1);
		}
		else if (pid == 0) { // 자식 프로세스
			char *newargv[] = {argv[3] , NULL};
			if (execve(argv[3], newargv, environ) == -1) {
				perror("Exec Error: ");
				return (-1);
			}
		}
		else { // 부모 프로세스
			if (waitpid(pid, NULL, 0) < 0) {
				perror("wait error");
				return (-1);
			}
			close(fd_zero);
			close(fd_one);
		}
	}
	return (0);
}
*/
