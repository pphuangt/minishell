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

static int	expand_cmd(t_cmd *cmd);

static int	expand_filename(char **filename)
{
	char	*str;
	char	*msg;

	str = expand_env_var(*filename, 0);
	if (!str)
	{
		err_ret("malloc expand environment variable");
		return (SYSTEM_ERROR);
	}
	if (!*str)
	{
		msg = ft_strjoin(*filename, ": ambiguous redirect");
		if (msg)
			err_ret(msg);
		free(str);
		return (SYSTEM_ERROR);
	}
	*filename = strip_matching_quotes(str);
	return (SUCCESS);
}

static int	expand_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	char		*str;
	int			argc;

	ecmd = (t_execcmd *)cmd;
	argc = 0;
	while (ecmd->argv[argc])
	{
		*ecmd->eargv[argc] = 0;
		str = expand_env_var(ecmd->argv[argc], 0);
		if (!str)
		{
			err_ret("expand environment variable");
			return (SYSTEM_ERROR);
		}
		if (*str)
			ecmd->argv[ecmd->argc++] = strip_matching_quotes(str);
		else
			free(str);
		argc++;
	}
	ecmd->argv[ecmd->argc] = 0;
	return (SUCCESS);
}

static int	expand_redir(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (expand_cmd(rcmd->cmd) == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	*rcmd->file.e = '\0';
	if (rcmd->mode != O_DSYNC)
	{
		if (expand_filename(&rcmd->file.s) == SYSTEM_ERROR)
			return (SYSTEM_ERROR);
		rcmd->file.e = rcmd->file.s;
	}
	return (SUCCESS);
}

static int	expand_cmd(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (SUCCESS);
	if (cmd->type == EXEC)
		return (expand_exec(cmd));
	else if (cmd->type == REDIR)
		return (expand_redir(cmd));
	else
	{
		pcmd = (t_pipecmd *)cmd;
		if (expand_cmd(pcmd->left) == SYSTEM_ERROR)
			return (SYSTEM_ERROR);
		return (expand_cmd(pcmd->right));
	}
}

t_shell	*expansion(t_shell *shell)
{
	if (shell->cmd && expand_cmd(shell->cmd) != SUCCESS)
		shell->exit_status = SYSTEM_ERROR;
	return (shell);
}
