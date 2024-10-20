/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:15:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/26 14:15:56 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_shell	*shell = NULL;

	if (!shell)
	{
		shell = (t_shell *)context;
		return ;
	}
	(void)info;
	shell->exit_status = TERM_BY_SIG + signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

static int	set_signal(int signum, void (*func), int flags)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = func;
	sa.sa_flags = flags;
	if (sigemptyset(&sa.sa_mask) < 0
		|| sigaction(signum, &sa, NULL) < 0)
	{
		err_ret("initialize signal");
		return (-1);
	}
	return (0);
}

void	reset_signal(void)
{
	set_signal(SIGQUIT, SIG_DFL, 0);
	set_signal(SIGINT, SIG_DFL, 0);
}

int	init_signal(t_shell *shell)
{
	signal_handler(0, 0, shell);
	if (set_signal(SIGQUIT, SIG_IGN, 0))
		return (-1);
	if (set_signal(SIGINT, &signal_handler, SA_RESTART | SA_SIGINFO))
		return (-1);
	return (0);
}
