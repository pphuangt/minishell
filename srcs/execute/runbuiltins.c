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

int	is_builtins(char *cmd_name)
{
	if (!cmd_name || !*cmd_name)
		return (0);
	if (!ft_strcmp(cmd_name, "echo")
		|| !ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "env")
		|| !ft_strcmp(cmd_name, "exit"))
		return (1);
	return (0);
}

int	runbuiltins_exec(t_execcmd *ecmd, t_shell *shell,
		int fd[2], int fd_size)
{
	char	*cmd_name;

	cmd_name = ecmd->argv[0];
	if (!ft_strcmp(cmd_name, "echo"))
		return (ft_echo(ecmd->argv, ecmd->argc));
	else if (!ft_strcmp(cmd_name, "cd"))
		return (ft_cd(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd_name, "export"))
		return (ft_export(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strcmp(cmd_name, "unset"))
		return (ft_unset(ecmd->argv, ecmd->argc, &shell->environ));
	else if (!ft_strcmp(cmd_name, "env"))
		return (ft_env(&shell->environ));
	else if (!ft_strcmp(cmd_name, "exit"))
		return (ft_exit(ecmd->argv, shell, fd, fd_size));
	return (SUCCESS);
}

static int	runbuiltins_redir(t_redircmd *rcmd, int fd[], int *fd_size)
{
	if (redirect(rcmd) != SUCCESS)
		return (SYSTEM_ERROR);
	if (is_new_fd(rcmd->fd, fd, *fd_size))
	{
		if (*fd_size == MAXARGS)
			return (close(rcmd->fd), err_msg(0, "too many fd"), SYSTEM_ERROR);
		fd[*fd_size] = rcmd->fd;
		(*fd_size)++;
	}
	return (SUCCESS);
}

void	runbuiltins(t_shell *shell)
{
	t_cmd	*cmd;
	int		std_fd[3];
	int		fd[MAXARGS];
	int		fd_size;

	if (save_std_fd(&std_fd[0], &std_fd[1], &std_fd[2]) < 0)
	{
		shell->exit_status = SYSTEM_ERROR;
		return ;
	}
	cmd = shell->cmd;
	fd_size = 0;
	while (cmd->type == REDIR
		&& runbuiltins_redir((t_redircmd *)cmd, fd, &fd_size) == SUCCESS)
		cmd = ((t_redircmd *)cmd)->cmd;
	if (cmd->type == EXEC)
		shell->exit_status = runbuiltins_exec((t_execcmd *)cmd, shell,
				fd, fd_size);
	else
		shell->exit_status = SYSTEM_ERROR;
	close_fd(fd, fd_size);
	if (restore_std_fd(&std_fd[0], &std_fd[1], &std_fd[2]) < 0)
		shell->exit_status = SYSTEM_ERROR;
}
