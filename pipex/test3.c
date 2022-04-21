#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			read_cnt;
	char		buff[128];
	int			pipe1fd[2];
	pid_t		pid;
	int			status;
	//extern char	**environ;

	if (pipe(pipe1fd) < 0)
		return (-1);
	dup2(pipe1fd[0], 0);
	dup2(pipe1fd[1], 1);
	close(pipe1fd[0]);
	close(pipe1fd[1]);
	write(1, "asjdf\n", strlen("asjdf\n"));
	//fprintf(stderr, "Parent: Send buff: %s\n", "asjdf");
	//fprintf(stderr, "Wait for child....\n");
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		char *cmd_argv[3];
		/*
		read_cnt = read(0, buff, sizeof(buff) - 1);
		buff[read_cnt] = 0;
		fprintf(stderr, "Child : Read buff: %s\n", buff);
		write(1, "kkkkk", strlen("kkkkk") + 1);
		fprintf(stderr, "Child : Send buff: %s\n", "kkkkk");
		*/
		cmd_argv[0] = "cat";
		//cmd_argv[1] = "-e";
		cmd_argv[1] = "-e";
		cmd_argv[2] = 0;
		execve("/bin/cat", cmd_argv, envp);
	}
	else
	{	
		waitpid(pid, &status, WNOHANG);
		fprintf(stderr, "===============\n");
		read_cnt = read(0, buff, sizeof(buff) - 1);
		buff[read_cnt] = 0;
		write(2, buff, read_cnt);
		//fprintf(stderr, "Parent: Receive buff: %s\n", buff);
	}
	/*
	read_cnt = read(0, buff, sizeof(buff) - 1);
	buff[read_cnt] = 0;
	fprintf(stderr, "%s\n", buff);
	write(1, "ssssssssss", ft_strlen("ssssssssss") + 1);
	*/
	return (0);
}
