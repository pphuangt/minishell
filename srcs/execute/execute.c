/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:50:49 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/07 15:50:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_name(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		return (((t_execcmd *)cmd)->argv[0]);
	else if (cmd->type == REDIR)
		return (get_cmd_name(((t_redircmd *)cmd)->cmd));
	return (NULL);
}

static int	is_builtins(char *cmd_name)
{
	size_t	cmd_name_len;

	if (!cmd_name || !*cmd_name)
		return (0);
	cmd_name_len = ft_strlen(cmd_name);
	if (!ft_strncmp(cmd_name, "echo", cmd_name_len)
		|| !ft_strncmp(cmd_name, "cd", cmd_name_len)
		|| !ft_strncmp(cmd_name, "pwd", cmd_name_len)
		|| !ft_strncmp(cmd_name, "export", cmd_name_len)
		|| !ft_strncmp(cmd_name, "unset", cmd_name_len)
		|| !ft_strncmp(cmd_name, "env", cmd_name_len)
		|| !ft_strncmp(cmd_name, "exit", cmd_name_len))
		return (1);
	return (0);
}

static void	runbuiltins(t_shell *shell)
{
	printf("run builtins\n");
	shell->exit_status = SUCCESS;
}

void	execute(t_shell *shell)
{
	char	*cmd_name;

	if (!shell->cmd)
		return ;
	if (expansion(shell) != SUCCESS)
		return ;
	if (shell->cmd->type == PIPE)
		runcmd(shell->cmd, shell);
	else
	{
		cmd_name = get_cmd_name(shell->cmd);
		if (is_builtins(cmd_name))
			runbuiltins(shell);
		else
			runcmd(shell->cmd, shell);
	}
}
