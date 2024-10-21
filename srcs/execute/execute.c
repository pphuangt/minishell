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

static void	print_exit_msg(int wstatus, int signum)
{
	char	*exit_msg;

	if (signum == SIGQUIT)
		exit_msg = "Quit";
	else
		exit_msg = "Segmentation fault";
	if (WCOREDUMP(wstatus))
	{
		ft_putstr_fd(exit_msg, STDERR_FILENO);
		ft_putendl_fd(" (core dumped)", STDERR_FILENO);
	}
	else
		ft_putendl_fd(exit_msg, STDERR_FILENO);
}

int	wait_runcmd(pid_t pid, int own)
{
	int	ret;
	int	wstatus;
	int	signum;

	ret = UNEXPECT_EXIT;
	if (waitpid(pid, &wstatus, 0) == -1)
		return (err_ret("waitpid"), ret);
	if (WIFEXITED(wstatus))
		ret = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		signum = WTERMSIG(wstatus);
		if (signum == SIGQUIT || signum == SIGSEGV)
			print_exit_msg(wstatus, signum);
		else if (own && signum == SIGINT)
			printf("\n");
		ret = TERM_BY_SIG + signum;
	}
	return (ret);
}

static char	*get_cmd_name(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		return (((t_execcmd *)cmd)->argv[0]);
	else if (cmd->type == REDIR)
		return (get_cmd_name(((t_redircmd *)cmd)->cmd));
	return (NULL);
}

int	is_builtins(char *cmd_name)
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

void	execute(t_shell *shell)
{
	char	*cmd_name;
	pid_t	pid;

	if (!shell->cmd || expansion(shell) != SUCCESS)
		return ;
	cmd_name = get_cmd_name(shell->cmd);
	if (shell->cmd->type != PIPE && is_builtins(cmd_name))
		runbuiltins(shell);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			err_ret("fork");
			shell->exit_status = SYSTEM_ERROR;
		}
		else if (pid == 0)
		{
			set_signal(SIGINT, SIG_IGN, 0);
			runcmd(shell->cmd, shell);
		}
		else
		{
			set_signal(SIGINT, SIG_IGN, 0);
			shell->exit_status = wait_runcmd(pid, 1);
			set_signal(SIGINT, &signal_handler, SA_RESTART | SA_SIGINFO);
		}
	}
}
