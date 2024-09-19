/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:17:14 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/16 11:17:21 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_filename(char **filename, char **env)
{
	char	*str;
	char	*msg;

	str = expand_env_var(*filename, env);
	if (!str)
	{
		err_ret("malloc expand environment variable");
		return (-1);
	}
	if (!*str)
	{
		msg = ft_strjoin(*filename, ": ambiguous redirect");
		if (msg)
			err_ret(msg);
		free(str);
		return (-1);
	}
	*filename = strip_matching_quotes(str);
	return (0);
}

static int	expand_exec(t_cmd *cmd, char **env)
{
	t_execcmd	*ecmd;
	char		*str;
	int			argc;

	ecmd = (t_execcmd *)cmd;
	argc = 0;
	while (ecmd->argv[argc])
	{
		*ecmd->eargv[argc] = 0;
		str = expand_env_var(ecmd->argv[argc], env);
		if (!str)
		{
			err_ret("expand environment variable");
			return (-1);
		}
		if (*str)
			ecmd->argv[ecmd->argc++] = strip_matching_quotes(str);
		else
			free(str);
		argc++;
	}
	ecmd->argv[ecmd->argc] = 0;
	return (0);
}

static int	expand_redir(t_cmd *cmd, char **env)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (expansion(rcmd->cmd, env) < 0)
		return (-1);
	*rcmd->file.e = '\0';
	if (rcmd->mode == O_DSYNC)
	{
		if (heredoc(rcmd, env) < 0)
			return (-1);
	}
	else
	{
		if (expand_filename(&rcmd->file.s, env) < 0)
			return (-1);
		rcmd->file.e = rcmd->file.s;
	}
	return (0);
}

int	expansion(t_cmd *cmd, char **env)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
	{
		if (expand_exec(cmd, env) < 0)
			return (-1);
	}
	else if (cmd->type == REDIR)
	{
		if (expand_redir(cmd, env) < 0)
			return (-1);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (expansion(pcmd->left, env) < 0)
			return (-1);
		if (expansion(pcmd->right, env) < 0)
			return (-1);
	}
	return (0);
}
