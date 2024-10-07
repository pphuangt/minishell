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

void	reset_shell(t_shell *shell)
{
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
}

char	*rl_gets(t_shell *shell, char **s, char *prompt, int history)
{
	*s = readline(prompt);
	shell->input = *s;
	shell->count_line++;
	if (*s && **s && history)
		add_history(*s);
	return (*s);
}

void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->input = NULL;
	shell->count_line = 0;
	shell->exit_status = 0;
}

int	main(void)
{
	t_shell	shell;
	char	*s;

	init_shell(&shell);
	if (init_signal(&shell) < 0)
		return (-1);
	while (rl_gets(&shell, &s, S_PROMPT, 1))
	{
		if (*s)
			execute(parsecmd(&shell, s));
		reset_shell(&shell);
	}
	printf("exit\n");
	return (0);
}
