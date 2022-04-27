#define MAX_PATH_LEN	128
#define BUFF_SIZE		10
#define	READ_END		0
#define WRITE_END		1

typedef struct s_here
{
	char	*limiter;
	int		is_here_doc;
} t_here_doc;

typedef struct s_arg
{
	int			argc;
	char		**envp;
	t_here_doc	here_info;
	int			cmd_cnt;
	char		*in_filename;
	char		*out_filename;
	char		**cmd_argv;
	char 		cmd_path[MAX_PATH_LEN];
} t_arg_info;

typedef struct s_fd 
{
	int		in_file;
	int		out_file;
	int		(*ppipe)[2];
} t_fd;

