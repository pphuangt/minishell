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
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"

# define METACHARACTER " \t\r\n\v|<>"
# define WHITESPACE " \t\r\n\v"
# define REDIR_O "<>"
# define QUOTE "\'\""
# define MAXLINE 4096
# define S_PROMPT "\033[1;32mminishell$ \033[0m"
# define MAXARGS 100

/*    exit_status    */
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
	t_cmd		*cmd;
	char		*input;
	t_environ	environ;
	size_t		count_line;
	int			exit_status;
}	t_shell;

/*    common    */
void	init_shell(t_shell *shell);
char	*rl_gets(t_shell *shell, char **s, char *prompt, int history);
void	reset_prompt(t_shell *shell);

/*    constructure    */
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd *subcmd, t_string *file, int mode, int fd);

/*    parsing    */
t_shell	*parsecmd(t_shell *shell, char *s);
int		peek(char **ps, char *es, char *tokens);
int		gettoken(char **ps, char *es, char **q, char **eq);
void	set_fd_mode(int tok, int *fd, int *mode);
int		valid_redir(char **ps, char *es, int *fd);
t_cmd	*err_parse_exec(t_cmd *cmd, char *msg, char *tok);

/*    expandation    */
int		expansion(t_shell *shell);
char	*expand_env_var(char *str, int exit_status, int heredoc);
int		cal_ret_size(char *str, int exit_status, int heredoc);
int		get_exit_status(char *dst, int exit_status);
int		is_invalid_filename(char *str);
void	handle_quote(char *qs, char c);
int		heredoc(t_redircmd *rcmd, t_shell *shell);
char	*strip_quotes(char *s);
int		set_argument(t_execcmd *ecmd, char *str);
void	clone_argument(char **dst, char **src);

/*    execute    */
void	execute(t_shell *shell);
void	runbuiltins(t_shell *shell);
int		save_std_fd(int *std_in, int *std_out, int *std_err);
int		restore_std_fd(int *std_in, int *std_out, int *std_err);
void	runcmd(t_cmd *cmd, t_shell *shell);
int		redirect(t_redircmd *rcmd, t_shell *shell);
int		is_new_fd(int new_fd, int fd[], int fd_size);
void	close_fd(int fd[], int fd_size);
int		wait_runcmd(pid_t pid);
int		is_builtins(char *cmd_name);
int		set_pathname(char **pathname, char *cmd_name);
int		is_dir(char *dir);
int		is_pathname_exist(char **pathname, char *cmd_name);
void	on_execve_error(char **pathname, t_shell *shell, int *fd, int fd_size);
void	clean_and_exit(t_shell *shell, int exit_status, int *fd, int fd_size);

/*    environ    */
char	*get_variable_environ(char **environ, char *str, size_t size);
int		init_environ(t_environ *environ);
void	free_environ(t_environ *environ);

/*    builtins    */
int		ft_echo(char **argv, int argc);
int		ft_cd(char **argv, int argc, t_environ *environ);
int		ft_pwd(char **argv, int argc, t_environ *environ);
int		ft_export(char **argv, int argc, t_environ *environ);
int		ft_unset(char **argv, int argc, t_environ *environ);
int		ft_env(char **argv, int argc, t_environ *environ);
int		ft_exit(char **argv, int argc, t_shell *shell);

/*    signals    */
int		init_signal(t_shell *shell);
void	reset_signal(void);

/*    utils    */
void	freecmd(t_cmd *cmd);
t_cmd	*reverse_redircmd(t_cmd *cmd);

/*    err    */
void	err_ret(const char *fmt);
void	err_tok(char *stok, char *etok);
void	err_filename(char *filename);
void	err_sys(const char *fmt, int exit_status);
void	err_msg(int error, const char *fmt);
void	err_exit(const char *fmt, t_shell *shell, int pipe[2]);

#endif
