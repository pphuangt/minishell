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

static void	runcmd_exec(t_execcmd *ecmd, t_shell *shell,
		int fd[], int fd_size)
{
	char	*pathname;

	if (!ecmd->argv[0])
		clean_and_exit(shell, SUCCESS, fd, fd_size);
	if (is_builtins(ecmd->argv[0]))
		runbuiltins(shell);
	else
	{
		pathname = NULL;
		if (!set_pathname(&pathname, ecmd->argv[0]))
			clean_and_exit(shell, SYSTEM_ERROR, fd, fd_size);
		if (!is_pathname_exist(&pathname, ecmd->argv[0]))
			clean_and_exit(shell, CMD_NOT_FOUND, fd, fd_size);
		execve(pathname, ecmd->argv, shell->environ.p);
		on_execve_error(&pathname, shell, fd, fd_size);
	}
	clean_and_exit(shell, shell->exit_status, fd, fd_size);
}

static void	runcmd_redir(t_cmd *cmd, t_shell *shell)
{
	t_redircmd	*rcmd;
	int			fd[MAXARGS];
	int			fd_size;

	fd_size = 0;
	while (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (redirect(rcmd, shell) != SUCCESS)
			clean_and_exit(shell, SYSTEM_ERROR, fd, fd_size);
		if (is_new_fd(rcmd->fd, fd, fd_size))
		{
			if (fd_size == MAXARGS)
			{
				err_ret("to many fd");
				clean_and_exit(shell, SYNTAX_ERROR, fd, fd_size);
			}
			fd[fd_size] = rcmd->fd;
			fd_size++;
		}
		cmd = rcmd->cmd;
	}
	runcmd_exec((t_execcmd *)cmd, shell, fd, fd_size);
}

static void	runcmd_pipe_right(t_cmd *cmd, t_shell *shell,
		int fd[2], pid_t left_pid)
{
	pid_t	right_pid;

	right_pid = fork();
	if (right_pid == -1)
		err_exit("pipe", shell, fd);
	else if (right_pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			err_exit("dup2", shell, fd);
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
		err_exit("pipe", shell, 0);
	left_pid = fork();
	if (left_pid == -1)
		err_exit("fork", shell, fd);
	else if (left_pid == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err_exit("dup", shell, fd);
		close(fd[0]);
		close(fd[1]);
		runcmd(pcmd->left, shell);
	}
	else
		runcmd_pipe_right(pcmd->right, shell, fd, left_pid);
}

void	runcmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->type == PIPE)
		runcmd_pipe_left((t_pipecmd *)cmd, shell);
	else
		runcmd_redir(cmd, shell);
}
