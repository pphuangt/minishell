/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:54:47 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/12 18:54:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	runcmd_exec(t_execcmd *ecmd, t_shell *shell)
{
	(void)ecmd;
	shell->exit_status = 0;
	printf("runcmd exec\n");
}

static void	runcmd_redir(t_redircmd *rcmd, t_shell *shell)
{
	(void)shell;
	runcmd(rcmd->cmd, shell);
}

static void	runcmd_pipe(t_pipecmd *pcmd, t_shell *shell)
{
	(void)shell;
	runcmd(pcmd->left, shell);
	runcmd(pcmd->right, shell);
}

void	runcmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->type == EXEC)
		runcmd_exec((t_execcmd *)cmd, shell);
	else if (cmd->type == REDIR)
		runcmd_redir((t_redircmd *)cmd, shell);
	else if (cmd->type == PIPE)
		runcmd_pipe((t_pipecmd *)cmd, shell);
}
