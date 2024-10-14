/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runbuiltins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:54:27 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/14 14:54:29 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	runbuiltins_exec(t_execcmd *ecmd, t_shell *shell)
{
	char	*cmd_name;
	size_t	cmd_name_len;

	cmd_name = ecmd->argv[0];
	cmd_name_len = ft_strlen(cmd_name);
	if (!ft_strncmp(cmd_name, "echo", cmd_name_len))
		return (ft_echo(ecmd->argv, ecmd->argc));
	else if (!ft_strncmp(cmd_name, "cd", cmd_name_len))
		return (ft_cd(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strncmp(cmd_name, "pwd", cmd_name_len))
		return (ft_pwd(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strncmp(cmd_name, "export", cmd_name_len))
		return (ft_export(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strncmp(cmd_name, "unset", cmd_name_len))
		return (ft_unset(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strncmp(cmd_name, "env", cmd_name_len))
		return (ft_env(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strncmp(cmd_name, "exit", cmd_name_len))
		return (ft_exit(shell));
	return (SUCCESS);
}

/*    if can't open or dup should close all fd that already open before    */
static int	runbuiltins_redir(t_redircmd *rcmd)
{
	int	fd;

	fd = open(rcmd->file.s, rcmd->mode);
	if (fd < 0)
		return (err_ret("open"), SYSTEM_ERROR);
	if (dup2(fd, rcmd->fd) < 0)
		return (close(fd), err_ret("dup2"), SYSTEM_ERROR);
	close(fd);
	return (SUCCESS);
}

void	runbuiltins(t_shell *shell)
{
	t_cmd	*cmd;
	int		std_fd[3];

	if (save_std_fd(&std_fd[0], &std_fd[1], &std_fd[2]) < 0)
	{
		shell->exit_status = SYSTEM_ERROR;
		return ;
	}
	cmd = shell->cmd;
	while (cmd->type == REDIR)
	{
		if (runbuiltins_redir((t_redircmd *)cmd) != SUCCESS)
		{
			shell->exit_status = SYSTEM_ERROR;
			return ;
		}
		cmd = ((t_redircmd *)cmd)->cmd;
	}
	shell->exit_status = runbuiltins_exec((t_execcmd *)cmd, shell);
	if (restore_std_fd(&std_fd[0], &std_fd[1], &std_fd[2]) < 0)
	{
		shell->exit_status = SYSTEM_ERROR;
		return ;
	}
}
