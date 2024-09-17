/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:24:15 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/13 11:24:29 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_process(t_redircmd *rcmd)
{
	int			fd[2];
	char		*input_line;

	if (pipe(fd) == -1)
		return (-1);
	input_line = readline(">");
	while (input_line)
	{
		if (ft_strncmp(input_line, rcmd->file.s, strlen(rcmd->file.s)) == 0)
		{
			free(input_line);
			break ;
		}
		if (write(fd[1], input_line, strlen(input_line)) == -1
			|| write(fd[1], "\n", 1) == -1)
			return (-1);
		free(input_line);
		input_line = readline(">");
	}
	close(fd[1]);
	rcmd->fd = fd[0];
	return (0);
}
