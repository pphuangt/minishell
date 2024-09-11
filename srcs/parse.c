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

static t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	t_cmd		*ncmd;
	int			tok;
	int			fd;
	int			mode;
	t_string	file;

	while (valid_redir(ps, es, &fd))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &file.s, &file.e) != 'a')
			return (err_parse_exec(cmd, "missing file for redirection"));
		if (fd == -1)
			set_default_fd(tok, &fd);
		set_mode(tok, &mode);
		ncmd = redircmd(cmd, &file, mode, fd);
		if (!ncmd)
			return (err_parse_exec(cmd, NULL));
		cmd = ncmd;
		while (*ps < es && ft_strchr(WHITESPACE, **ps))
			(*ps)++;
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*ret;
	t_cmd		*cmd;
	t_execcmd	*exec_cmd;
	t_string	string;
	int			tok;

	ret = execcmd();
	if (!ret)
		return (NULL);
	exec_cmd = (t_execcmd *)ret;
	exec_cmd->argc = 0;
	while (*ps < es && !peek(ps, es, " \t\r\n\v|"))
	{
		cmd = parseredirs(ret, ps, es);
		if (!cmd)
			return (NULL);
		ret = cmd;
		tok = gettoken(ps, es, &string.s, &string.e);
		if (tok < 0)
			return (err_parse_exec(ret, "no closing quote"));
		else if (tok == 'a')
		{
			exec_cmd->argv[exec_cmd->argc] = string.s;
			exec_cmd->eargv[exec_cmd->argc++] = string.e;
			if (exec_cmd->argc == MAXARGS + 1)
				return (err_parse_exec(ret, "to many args"));
		}
	}
	exec_cmd->argv[exec_cmd->argc] = 0;
	exec_cmd->eargv[exec_cmd->argc] = 0;
	return (ret);
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
