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

static int	expand_exec(t_cmd *cmd, char **envp)
{
	t_execcmd	*ecmd;
	char		*str;

	ecmd = (t_execcmd *)cmd;
	while (ecmd->argv[ecmd->argc])
	{
		*ecmd->eargv[ecmd->argc] = 0;
		str = expand_env_var(ecmd->argv[ecmd->argc], envp);
		if (!str)
			return (-1);
		strip_matching_quotes(str);
		ecmd->argv[ecmd->argc] = str;
		ecmd->argc++;
	}
	remove_null_entries(ecmd->argv);
	return (0);
}

static int	expand_redir(t_cmd *cmd, char **envp)
{
	t_redircmd	*rcmd;
	char		*str;

	rcmd = (t_redircmd *)cmd;
	if (expansion(rcmd->cmd, envp) < 0)
		return (-1);
	*rcmd->file.e = '\0';
	str = expand_env_var(rcmd->file.s, envp);
	if (!str)
		return (-1);
	strip_matching_quotes(str);
	rcmd->file.s = str;
	rcmd->file.e = str;
	if (rcmd->mode == O_DSYNC)
	{
		if (heredoc_process(rcmd) < 0)
			return (-1);
	}
	return (0);
}

int	expansion(t_cmd *cmd, char **envp)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
	{
		if (expand_exec(cmd, envp) < 0)
			return (-1);
	}
	else if (cmd->type == REDIR)
	{
		if (expand_redir(cmd, envp) < 0)
			return (-1);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (expansion(pcmd->left, envp) < 0)
			return (-1);
		if (expansion(pcmd->right, envp) < 0)
			return (-1);
	}
	return (0);
}
