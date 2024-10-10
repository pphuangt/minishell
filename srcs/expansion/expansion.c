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

	str = expand_env_var(*filename, 0, 0);
	if (!str)
		return (err_ret("malloc"), SYSTEM_ERROR);
	if (!*str || is_invalid_filename(str))
		return (err_filename(*filename), free(str), SYSTEM_ERROR);
	*filename = strip_quotes(str);
	return (SUCCESS);
}

static int	expand_exec(t_cmd *cmd)
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
		str = expand_env_var(argv[argc], 0, 0);
		if (!str)
			return (err_ret("expand environment variable"), SYSTEM_ERROR);
		if (set_argument(ecmd, str) == SYSTEM_ERROR)
			return (err_ret("expand environment variable"), SYSTEM_ERROR);
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

int	expansion(t_shell *shell)
{
	if (expand_cmd(shell->cmd) == SYSTEM_ERROR)
	{
		shell->exit_status = SYSTEM_ERROR;
		return (SYSTEM_ERROR);
	}
	return (SUCCESS);
}
