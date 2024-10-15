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

static int	is_new_fd(int new_fd, int fd[], int fd_size)
{
	int	i;

	i = 0;
	while (i < fd_size)
	{
		if (fd[i++] == new_fd)
			return (0);
	}
	return (1);
}

static int	runbuiltins_redir(t_redircmd *rcmd, t_shell *shell,
		int fd[], int *fd_size)
{
	if (runredir(rcmd, shell) != SUCCESS)
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

static void	close_fd(int fd[], int fd_size)
{
	int	i;

	i = 0;
	while (i < fd_size)
		close(fd[i++]);
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
		&& runbuiltins_redir((t_redircmd *)cmd, shell, fd, &fd_size) == SUCCESS)
		cmd = ((t_redircmd *)cmd)->cmd;
	if (cmd->type == EXEC)
		shell->exit_status = runbuiltins_exec((t_execcmd *)cmd, shell);
	else
		shell->exit_status = SYSTEM_ERROR;
	close_fd(fd, fd_size);
	if (restore_std_fd(&std_fd[0], &std_fd[1], &std_fd[2]) < 0)
		shell->exit_status = SYSTEM_ERROR;
}
