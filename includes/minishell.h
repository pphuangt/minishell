/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:57 by pphuangt          #+#    #+#             */
/*   Updated: 2024/06/24 15:40:59 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "libft.h"

# define METACHARACTER " \t\r\n\v|<>"
# define WHITESPACE " \t\r\n\v"
# define REDIR_O "<>"
# define QUOTE "\'\""
# define MAXLINE 4096
# define S_PROMPT "\033[1;32mminishell$ \033[0m"
# define MAXARGS 10

typedef enum s_type
{
	EXEC,
	REDIR,
	PIPE,
}	t_type;

typedef struct s_cmd
{
	t_type	type;
}	t_cmd;

typedef struct s_execcmd
{
	t_type	type;
	char	*argv[MAXARGS + 1];
	char	*eargv[MAXARGS + 1];
	int		argc;
}	t_execcmd;

typedef struct s_string
{
	char	*s;
	char	*e;
}	t_string;

typedef struct s_redircmd
{
	t_type			type;
	struct s_cmd	*cmd;
	struct s_string	file;
	int				mode;
	int				fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_environ
{
	char	**p;
	size_t	len;
	size_t	size;
}	t_environ;

typedef struct s_shell
{
	t_environ	environ;
	size_t		size;
	size_t		count_line;
	int			exit_status;
}	t_shell;

/*    constructure    */
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd *subcmd, t_string *file, int mode, int fd);

/*    parsing    */
t_cmd	*parsecmd(char *s);
int		peek(char **ps, char *es, char *tokens);
int		gettoken(char **ps, char *es, char **q, char **eq);
void	set_fd_mode(int tok, int *fd, int *mode);
int		valid_redir(char **ps, char *es, int *fd);
t_cmd	*err_parse_exec(t_cmd *cmd, char *msg, char *tok);

/*    expandation    */
int		expansion(t_shell *shell, t_cmd *cmd);
char	*expand_env_var(char *str);
int		heredoc(t_shell *shell, t_redircmd *rcmd);
char	*strip_matching_quotes(char *s);

/*    environ    */
int		init_environ(t_shell *shell);
char	*get_variable_environ(char *str, size_t size);
int		add_variable_environ(t_shell *shell, char *var);
int		remove_vairable_environ(t_shell *shell, char *name, size_t size);
void	free_envp(t_shell *shell);

/*    signals    */
int		init_signal(t_shell *shell);

/*    utils    */
void	freecmd(t_cmd *cmd);
void	printcmd(t_cmd *cmd);
t_cmd	*reverse_redircmd(t_cmd *cmd);

/*    err    */
void	err_ret(const char *fmt);
void	err_sys(const char *fmt);
void	err_msg(int error, const char *fmt);
void	err_exit(int error, const char *fmt);

#endif
