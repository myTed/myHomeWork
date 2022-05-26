/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:56:50 by kyolee            #+#    #+#             */
/*   Updated: 2022/04/28 20:04:57 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# define MAX_PATH_LEN	128
# define BUFF_SIZE		10
# define READ_END		0
# define WRITE_END		1

typedef struct s_here
{
	char	*limiter;
	int		is_here_doc;
}	t_here_doc;

typedef struct s_arg
{
	int			argc;
	char		**envp;
	t_here_doc	here_info;
	int			cmd_cnt;
	char		*in_filename;
	char		*out_filename;
	char		**cmd_argv;
	char		cmd_path[MAX_PATH_LEN];
}	t_arg_info;

typedef struct s_fd
{
	int		in_file;
	int		out_file;
	int		(*ppipe)[2];
}	t_fd;

int	malloc_pipe(int argc, t_fd *ptfds, t_arg_info *parg);
int	free_pipe(t_fd *ptfds);
int	fill_arg_inform(int argc, char **argv, char **envp, t_arg_info *parg);
int	is_valid_argc(int argc, char **argv, char *here_doc);
int	get_cmd_argv_malloc(char *cmd_str, t_arg_info *parg);
int	free_cmd_argv(t_arg_info *parg);
int	wait_for_child(int pid, char **cmd_argv);
int	get_result_which_cmd(
		int *ppipefd,
		t_arg_info *parg,
		char **cmd_argv
		);
int	get_cmd_path(t_arg_info *parg);
int	exec_cmd(int cmd_idx, char **argv, t_fd *ptfds, t_arg_info *parg);
int	wait_for_children(int last_cmd_pid);
int	exec_cmd_loop(
		char **argv,
		t_arg_info *parg,
		t_fd *ptfds
		);
int	get_fd_file(int cmd_idx, t_fd *ptfds, t_arg_info *parg);
int	close_unused_fd(int cmd_idx, t_fd *ptfds, t_arg_info *parg);
int	close_all_fd(t_fd *ptfds, t_arg_info *parg);
int	dup_stdin_stdout(int cmd_idx, t_fd *ptfds, t_arg_info *parg);
int	open_infile_for_read(t_arg_info *parg, int *pfd);
int	open_infile(t_arg_info *parg, int *pfd);
int	open_outfile(t_arg_info *parg, int *pfd);
int	make_heredoc_file(t_arg_info *parg);
#endif
