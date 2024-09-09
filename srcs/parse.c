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

static t_cmd	*err_exec(t_execcmd *exec_cmd, char *msg)
{
	err_msg(0, msg);
	free(exec_cmd);
	return (NULL);
}

static t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	t_f		f;

	while (peek(ps, es, REDIR_O))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &f.file, &f.efile) != 'a')
		{
			err_ret("missing file for redirection");
			return (NULL);
		}
		if (tok == '<')
			cmd = redircmd(cmd, &f, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, &f, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(cmd, &f, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok == '-')
			cmd = redircmd(cmd, &f, O_DSYNC, 0);
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execcmd	*exec_cmd;
	char		*q;
	char		*eq;

	cmd = execcmd();
	if (!cmd)
		return (NULL);
	exec_cmd = (t_execcmd *)cmd;
	exec_cmd->argc = 0;
	cmd = parseredirs(cmd, ps, es);
	while (*ps < es && !peek(ps, es, METACHARACTER))
	{
		if (gettoken(ps, es, &q, &eq) < 0)
			return (err_exec(exec_cmd, "no closing quote"));
		exec_cmd->argv[exec_cmd->argc] = q;
		exec_cmd->eargv[exec_cmd->argc++] = eq;
		if (exec_cmd->argc == MAXARGS + 1)
			return (err_exec(exec_cmd, "to many args"));
		cmd = parseredirs(cmd, ps, es);
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
