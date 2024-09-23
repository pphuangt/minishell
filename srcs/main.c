/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:44:44 by pphuangt          #+#    #+#             */
/*   Updated: 2024/06/24 15:44:46 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	peek(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}

int	init_signal(int signum, void (*func), int flags)
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

int	main(void)
{
	t_cmd	*cmd;
	char	*s;

	if (init_signal(SIGQUIT, SIG_IGN, 0) < 0)
		return (1);
	s = readline(S_PROMPT);
	while (s)
	{
		if (*s)
		{
			add_history(s);
			cmd = parsecmd(s);
			if (expansion(cmd) == 0)
				printcmd(cmd);
			freecmd(cmd);
		}
		free(s);
		s = readline(S_PROMPT);
	}
	printf("exit\n");
	return (0);
}
