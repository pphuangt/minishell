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
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

# define METACHARACTER " \t\r\n\v|<>"
# define WHITESPACE " \t\r\n\v"
# define REDIR_O "<>"
# define QUOTE "\'\""
# define MAXLINE 4096
# define S_PROMPT "\033[1;32m$ \033[0m"
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
	int		isexpand;
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
	struct s_string	heredoc;
	int				mode;
	int				fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	t_type	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

/*    constructure    */
t_cmd	*execcmd(void);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*redircmd(t_cmd *subcmd, t_string *file, int mode, int fd);

/*    parsing    */
t_cmd	*parsecmd(char *s);
int		peek(char **ps, char *es, char *tokens);
int		gettoken(char **ps, char *es, char **q, char **eq);
void	set_default_fd(int tok, int *fd);
void	set_mode(int tok, int *mode);
int		valid_redir(char **ps, char *es, int *fd);
t_cmd	*err_parse_exec(t_cmd *cmd, char *msg);
int		heredoc_process(t_cmd *cmd);

/*    expandation    */
int		expandation(t_cmd *cmd, char **envp);
int		join_var(char **token, char **s, int *i);
int		join_util(char **token, char *s);
void	remove_null(char **argv);
void	remove_quote(char *s);
int		isvar(char c);

/*    env    */
char	*get_env(char *str, char **envp);

/*    utils    */
void	freecmd(t_cmd *cmd);
void	printcmd(t_cmd *cmd);

/*    err    */
void	err_ret(const char *fmt);
void	err_sys(const char *fmt);
void	err_msg(int error, const char *fmt);
void	err_exit(int error, const char *fmt);

#endif
