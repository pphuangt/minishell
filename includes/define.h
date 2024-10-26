#define DEFINE_H
# define DEFINE_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"

# define BUF_SIZE 4096
# define PROMPT "\1\e[3;34m\e[0m\e[1;34m\2minishell$\1\e[0m\2 "
# define HD_PROMPT "\1\e[1;37m\2>\1\e[0m\2 "

# define SUCCESS 0
# define SYSTEM_ERROR 1
# define SYNTAX_ERROR 2
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127
# define TERM_BY_SIG 128
# define UNEXPECT_EXIT 128

typedef enum s_type
{
	EXEC,
	REDIR,
	PIPE,
}	t_type;

typedef enum s_mode
{
	REDIR_IN,
	REDIR_OUT,
	APPEN,
	HEREDOC
}	t_mode;

typedef struct s_cmd
{
	t_type	type;
}	t_cmd;

typedef struct s_execcmd
{
	t_type		type;
	t_list		*argv;
	size_t		argc;
}	t_execcmd;

typedef struct s_redircmd
{
	t_type	type;
	t_cmd	*cmd;
	t_mode	mode;
	int		fd;
	char	*filename;
	char	*here_end;
}	t_redircmd;

typedef struct s_pipecmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_environment_node
{
	char	*key;
	char	*value;
}	t_environment_node;

typedef struct s_shell
{
	int				is_interactive;
	t_list			*env_list;
	size_t			count_line;
	char			*input;
	t_cmd			*cmd;
	unsigned char	exit_code;
	t_list			*child_pid_list;
}	t_shell;

#endif
