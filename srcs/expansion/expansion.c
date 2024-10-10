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

static int	expand_cmd(t_cmd *cmd, int exit_status);

static int	expand_filename(char **filename, int exit_status)
{
	char	*str;

	str = expand_env_var(*filename, exit_status, 0);
	if (!str)
		return (err_ret("malloc"), SYSTEM_ERROR);
	if (!*str || is_invalid_filename(str))
		return (err_filename(*filename), free(str), SYSTEM_ERROR);
	*filename = strip_quotes(str);
	return (SUCCESS);
}

static int	expand_exec(t_cmd *cmd, int exit_status)
{
	t_execcmd	*ecmd;
	char		*argv[MAXARGS + 1];
	char		*str;
	int			argc;

	ecmd = (t_execcmd *)cmd;
	argc = 0;
	clone_argument(argv, ecmd->argv);
	while (argv[argc])
	{
		*ecmd->eargv[argc] = 0;
		str = expand_env_var(argv[argc], exit_status, 0);
		if (!str)
			return (err_ret("malloc"), SYSTEM_ERROR);
		if (set_argument(ecmd, str) == SYSTEM_ERROR)
			return (err_ret("malloc"), SYSTEM_ERROR);
		argc++;
	}
	ecmd->argv[ecmd->argc] = 0;
	return (SUCCESS);
}

static int	expand_redir(t_cmd *cmd, int exit_status)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (expand_cmd(rcmd->cmd, exit_status) == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	*rcmd->file.e = '\0';
	if (rcmd->mode != O_DSYNC)
	{
		if (expand_filename(&rcmd->file.s, exit_status) == SYSTEM_ERROR)
			return (SYSTEM_ERROR);
		rcmd->file.e = rcmd->file.s;
	}
	return (SUCCESS);
}

static int	expand_cmd(t_cmd *cmd, int exit_status)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (SUCCESS);
	if (cmd->type == EXEC)
		return (expand_exec(cmd, exit_status));
	else if (cmd->type == REDIR)
		return (expand_redir(cmd, exit_status));
	else
	{
		pcmd = (t_pipecmd *)cmd;
		if (expand_cmd(pcmd->left, exit_status) == SYSTEM_ERROR)
			return (SYSTEM_ERROR);
		return (expand_cmd(pcmd->right, exit_status));
	}
}

int	expansion(t_shell *shell)
{
	if (expand_cmd(shell->cmd, shell->exit_status) == SYSTEM_ERROR)
	{
		shell->exit_status = SYSTEM_ERROR;
		return (SYSTEM_ERROR);
	}
	return (SUCCESS);
}
