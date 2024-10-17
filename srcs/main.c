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
	char	*s;

	init_shell(&shell);
	if (init_signal(&shell) < 0 || init_environ(&shell.environ) < 0)
		return (-1);
	while (rl_gets(&shell, &s, S_PROMPT, 1))
	{
		if (*s)
			execute(parsecmd(&shell, s));
		reset_prompt(&shell);
	}
	free_environ(&shell.environ);
	printf("exit\n");
	return (0);
}
