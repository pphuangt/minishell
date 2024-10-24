/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:41:55 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 21:42:02 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	shell->is_interactive = isatty(STDIN_FILENO);
	shell->cmd = NULL;
	shell->input = NULL;
	shell->count_line = 0;
	shell->exit_status = 0;
}

void	reset_prompt(t_shell *shell)
{
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
}

char	*rl_gets(t_shell *shell, char **s, char *prompt, int history)
{
	if (shell->is_interactive)
	{
		*s = readline(prompt);
		if (*s && **s && history)
			add_history(*s);
	}
	else
	{
		*s = get_next_line(STDIN_FILENO);
		if (*s && **s)
			(*s)[ft_strlen(*s) - 1] = '\0';
	}
	shell->input = *s;
	shell->count_line++;
	return (*s);
}
