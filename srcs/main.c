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

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*input_line;

	(void)argc;
	(void)argv;
	input_line = readline(S_PROMPT);
	while (input_line)
	{
		if (*input_line)
		{
			add_history(input_line);
			cmd = parsecmd(input_line, envp);
			printcmd(cmd);
		}
		freecmd(cmd);
		free(input_line);
		input_line = readline(S_PROMPT);
	}
	return (0);
}
