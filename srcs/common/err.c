/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:24:15 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/02 08:24:18 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_doit(int error, const char *fmt)
{
	char	buff[MAXLINE];

	ft_strlcpy(buff, "minishell: ", MAXLINE);
	if (fmt)
		ft_strlcat(buff, fmt, MAXLINE - 1);
	if (error)
	{
		if (fmt)
			ft_strlcat(buff, ": ", MAXLINE - 1);
		ft_strlcat(buff, strerror(error), MAXLINE - 1);
	}
	ft_strlcat(buff, "\n", MAXLINE - 1);
	ft_putstr_fd(buff, STDERR_FILENO);
}

void	err_ret(const char *fmt)
{
	err_doit(errno, fmt);
}

void	err_msg(int error, const char *fmt)
{
	err_doit(error, fmt);
}

void	err_exit(const char *fmt, t_shell *shell, int pipe[2])
{
	err_doit(errno, fmt);
	freecmd(shell->cmd);
	free_environ(&shell->environ);
	free(shell->input);
	rl_clear_history();
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
	exit(SYSTEM_ERROR);
}
