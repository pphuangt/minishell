/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:02:29 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/30 15:02:35 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	runcmd_recursive(t_cmd *cmd);

static void	runcmd_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	char		*pathname;
	extern char	**environ;

	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == 0)
		exit(0);
	pathname = ecmd->argv[0];
	if (!ft_strchr(ecmd->argv[0], '/'))
		pathname = search_pathname(ecmd->argv[0], ft_strlen(ecmd->argv[0]));
	if (!pathname)
	{
		ft_putstr_fd(ecmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(0);
	}
	execve(pathname, ecmd->argv, environ);
	err_ret(pathname);
	if (pathname != ecmd->argv[0])
		free(pathname);
}

static void	runcmd_redir(t_cmd *cmd)
{
	(void)cmd;
	return ;
}

static void	runcmd_pipe(t_cmd *cmd)
{
	int			fd[2];
	t_pipecmd	*pcmd;
	int			wstatus;

	if (pipe(fd) < 0)
	{
		err_ret("pipe");
		return ;
	}
	pcmd = (t_pipecmd *)cmd;
	if (fork() == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		runcmd_recursive(pcmd->left);
	}
	if (fork() == 0)
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		runcmd_recursive(pcmd->right);
	}
	close(fd[0]);
	close(fd[1]);
	wait(&wstatus);
	wait(&wstatus);
}

static void	runcmd_recursive(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		runcmd_exec(cmd);
	else if (cmd->type == REDIR)
		runcmd_redir(cmd);
	else if (cmd->type == PIPE)
		runcmd_pipe(cmd);
}

void	runcmd(t_cmd *cmd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		err_ret("fork");
		return ;
	}
	if (pid == 0)
	{
		runcmd_recursive(cmd);
		exit(0);
	}
	else
		wait(&wstatus);
}
