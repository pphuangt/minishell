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
	char	*pathname;

	if (!ecmd->argv[0])
		exit(SUCCESS);
	pathname = ecmd->argv[0];
	execve(pathname, ecmd->argv, shell->environ.p);
	err_exit(errno, pathname, CMD_NOT_EXEC);
}

static void	runcmd_redir(t_redircmd *rcmd, t_shell *shell)
{
	if (redirect(rcmd, shell) != SUCCESS)
		exit(SYSTEM_ERROR);
	runcmd(rcmd->cmd, shell);
}

static void	runcmd_pipe_right(t_cmd *cmd, t_shell *shell,
	int fd[2], pid_t left_pid)
{
	pid_t	right_pid;

	right_pid = fork();
	if (right_pid == -1)
		err_exit(errno, "pipe", SYSTEM_ERROR);
	else if (right_pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		runcmd(cmd, shell);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		wait_runcmd(left_pid);
		exit(wait_runcmd(right_pid));
	}
}

static void	runcmd_pipe_left(t_pipecmd *pcmd, t_shell *shell)
{
	int		fd[2];
	pid_t	left_pid;

	if (pipe(fd) == -1)
		err_exit(errno, "pipe", SYSTEM_ERROR);
	left_pid = fork();
	if (left_pid == -1)
		err_exit(errno, "fork", SYSTEM_ERROR);
	else if (left_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		runcmd(pcmd->left, shell);
	}
	else
		runcmd_pipe_right(pcmd->right, shell, fd, left_pid);
}

void	runcmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->type == EXEC)
		runcmd_exec((t_execcmd *)cmd, shell);
	else if (cmd->type == REDIR)
		runcmd_redir((t_redircmd *)cmd, shell);
	else if (cmd->type == PIPE)
		runcmd_pipe_left((t_pipecmd *)cmd, shell);
	exit(SUCCESS);
}
