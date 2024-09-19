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

static void	remove_null_entries(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			argv[j++] = argv[i];
		i++;
	}
	if (j != 0)
		argv[j] = 0;
}

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
		{
			err_ret("expand environment variable");
			return (-1);
		}
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
	if (rcmd->mode == O_DSYNC)
	{
		if (heredoc(rcmd, envp) < 0)
			return (-1);
	}
	else
	{
		str = expand_env_var(rcmd->file.s, envp);
		if (!str)
		{
			err_ret("expand environment variable");
			return (-1);
		}
		rcmd->file.s = str;
		rcmd->file.e = str;
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
