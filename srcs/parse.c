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
	while (*ps < es && !peek(ps, es, METACHARACTER))
	{
		if (exec_cmd->argc == MAXARGS)
			return (err_exec(exec_cmd, "to many args"));
		else if (gettoken(ps, es, &q, &eq) < 0)
			return (err_exec(exec_cmd, "no closing quote"));
		exec_cmd->argv[exec_cmd->argc] = q;
		exec_cmd->eargv[exec_cmd->argc++] = eq;
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

t_cmd	*parsecmd(char	*s, char **envp)
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
	if (expandation(cmd, envp) < 0)
	{
		err_sys("expanding malloc");
		freecmd(cmd);
		return (NULL);
	}
	return (cmd);
}
