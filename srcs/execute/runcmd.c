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

/*
static pid_t	runpipe(t_cmd *cmd, t_shell *shell, int input_fd, int output_fd, int close_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		err_exit(errno, "fork", SYSTEM_ERROR);
	else if (pid == 0)
	{
		dup2(close_fd, output_fd);
		close(close_fd);
		close(input_fd);
		runcmd(cmd, shell);
	}
	return (pid);
}
*/

static void	runcmd_pipe(t_pipecmd *pcmd, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		err_exit(errno, "pipe", SYSTEM_ERROR);
	pid = fork();
	if (pid == -1)
		err_exit(errno, "fork", SYSTEM_ERROR);
	else if (pid == 0)
	{
		dup2(fd[0], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		runcmd(cmd, shell);
	}
	else
		wait_runcmd();
}
	/*
	left_pid = runpipe(pcmd->left, shell, fd[0], STDOUT_FILENO, fd[1]);
	right_pid = runpipe(pcmd->right, shell, fd[1], STDIN_FILENO, fd[0]);
	close(fd[0]);
	close(fd[1]);
	wait_runcmd(left_pid);
	wait_runcmd(right_pid);
	*/

void	runcmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->type == EXEC)
		runcmd_exec((t_execcmd *)cmd, shell);
	else if (cmd->type == REDIR)
		runcmd_redir((t_redircmd *)cmd, shell);
	else if (cmd->type == PIPE)
		runcmd_pipe((t_pipecmd *)cmd, shell);
	exit(SUCCESS);
}
