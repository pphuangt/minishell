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
	*s = readline(prompt);
	shell->input = *s;
	shell->count_line++;
	if (*s && **s && history)
		add_history(*s);
	return (*s);
}
