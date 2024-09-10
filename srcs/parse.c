/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:42:02 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/04 13:42:09 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, t_string *string)
{
	int			tok;
	int			fd;
	int			mode;
	t_string	file;

	fd = 0;
	if (string && *ps < es && ft_strchr(REDIR_O, **ps))
		fd = 1;
	while (peek(ps, es, REDIR_O))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &file.s, &file.e) != 'a')
		{
			err_ret("missing file for redirection");
			return (NULL);
		}
		set_fd(tok, &fd, string);
		set_mode(tok, &mode);
		cmd = redircmd(cmd, &file, mode, fd);
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execcmd	*exec_cmd;
	t_string	string;

	cmd = execcmd();
	if (!cmd)
		return (NULL);
	exec_cmd = (t_execcmd *)cmd;
	exec_cmd->argc = 0;
	while (*ps < es && !peek(ps, es, META_O))
	{
		if (gettoken(ps, es, &string.s, &string.e) < 0)
			return (err_parse_exec(exec_cmd, "no closing quote"));
		cmd = parseredirs(cmd, ps, es, &string);
		if (string.s != NULL)
		{
			exec_cmd->argv[exec_cmd->argc] = string.s;
			exec_cmd->eargv[exec_cmd->argc++] = string.e;
			if (exec_cmd->argc == MAXARGS + 1)
				return (err_parse_exec(exec_cmd, "to many args"));
		}
	}
	exec_cmd->argv[exec_cmd->argc] = 0;
	exec_cmd->eargv[exec_cmd->argc] = 0;
	return (cmd);
}

static t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_cmd	*pipe_cmd;

	cmd = parseexec(ps, es);
	if (!cmd)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		pipe_cmd = parsepipe(ps, es);
		if (!pipe_cmd)
		{
			freecmd(cmd);
			return (NULL);
		}
		cmd = pipecmd(cmd, pipe_cmd);
		if (!cmd)
		{
			freecmd(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_cmd	*parsecmd(char	*s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parsepipe(&s, es);
	if (!cmd)
		return (NULL);
	if (s != es)
	{
		err_msg(0, "invalid args");
		freecmd(cmd);
		return (NULL);
	}
	return (cmd);
}
