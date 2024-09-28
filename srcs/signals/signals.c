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
	(void)signum;
	(void)info;
	shell->exit_status = 1;
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
		err_sys("initialize signal");
		return (-1);
	}
	return (0);
}

int	init_signal(t_shell *shell)
{
	shell->count_line = 0;
	signal_handler(0, 0, shell);
	if (set_signal(SIGQUIT, SIG_IGN, 0))
		return (-1);
	if (set_signal(SIGINT, &signal_handler, SA_RESTART | SA_SIGINFO))
		return (-1);
	return (0);
}
