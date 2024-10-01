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

int	main(void)
{
	t_shell	shell;
	t_cmd	*cmd;
	char	*s;

	if (init_signal(&shell) < 0 || init_environ(&shell) < 0)
		return (-1);
	s = readline(S_PROMPT);
	while (s)
	{
		shell.count_line++;
		if (*s)
		{
			add_history(s);
			cmd = parsecmd(&shell, s);
			if (expansion(&shell, cmd) == 0)
				runcmd(cmd);
			freecmd(cmd);
		}
		free(s);
		s = readline(S_PROMPT);
	}
	printf("exit\n");
	return (0);
}
