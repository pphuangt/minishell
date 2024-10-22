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

static int	expand_cmd(t_cmd *cmd, t_shell *shell);

static int	expand_filename(char **filename, int exit)
{
	char	*str;

	str = expand_env_var(*filename, exit, 0);
	if (!str)
		return (err_ret("malloc"), SYSTEM_ERROR);
	if (!*str || is_invalid_filename(str))
		return (err_filename(*filename), free(str), SYSTEM_ERROR);
	*filename = strip_quotes(str);
	return (SUCCESS);
}

static int	expand_exec(t_cmd *cmd, int exit)
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
		str = expand_env_var(argv[argc], exit, 0);
		if (!str)
			return (err_ret("malloc"), SYSTEM_ERROR);
		if (set_argument(ecmd, str) == SYSTEM_ERROR)
			return (err_ret("malloc"), SYSTEM_ERROR);
		argc++;
	}
	ecmd->argv[ecmd->argc] = 0;
	return (SUCCESS);
}

static int	expand_redir(t_cmd *cmd, t_shell *shell)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	*rcmd->file.e = '\0';
	if (rcmd->mode != O_DSYNC)
	{
		if (expand_filename(&rcmd->file.s, shell->exit_status) != SUCCESS)
			return (SYSTEM_ERROR);
		rcmd->file.e = rcmd->file.s;
	}
	else if (heredoc(rcmd, shell) < 0)
		return (SYSTEM_ERROR);
	if (expand_cmd(rcmd->cmd, shell) == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	return (SUCCESS);
}

static int	expand_cmd(t_cmd *cmd, t_shell *shell)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (SUCCESS);
	if (cmd->type == EXEC)
		return (expand_exec(cmd, shell->exit_status));
	else if (cmd->type == REDIR)
		return (expand_redir(cmd, shell));
	else
	{
		pcmd = (t_pipecmd *)cmd;
		if (expand_cmd(pcmd->left, shell) == SYSTEM_ERROR)
			return (SYSTEM_ERROR);
		return (expand_cmd(pcmd->right, shell));
	}
}

int	expansion(t_shell *shell)
{
	if (expand_cmd(shell->cmd, shell) == SYSTEM_ERROR)
	{
		if (shell->exit_status != TERM_BY_SIG + SIGINT)
			shell->exit_status = SYSTEM_ERROR;
		return (SYSTEM_ERROR);
	}
	return (SUCCESS);
}
