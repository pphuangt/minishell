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

void	strip_matching_quotes(char *s)
{
	int		i;
	int		j;
	char	quote_status;

	if (!s)
		return ;
	i = 0;
	j = 0;
	quote_status = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(QUOTE, s[i]))
		{
			if (quote_status == s[i])
				quote_status = 0;
			else if (quote_status == 0)
				quote_status = s[i];
			else
				s[j++] = s[i];
		}
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

int	heredoc(t_redircmd *rcmd)
{
	int			fd[2];
	char		*input_line;

	if (rcmd->mode != O_DSYNC)
		return (0);
	if (pipe(fd) == -1)
	{
		err_ret("pipe");
		return (-1);
	}
	input_line = readline(">");
	while (input_line)
	{
		if (ft_strncmp(input_line, rcmd->file.s, -1) == 0)
		{
			free(input_line);
			break ;
		}
		ft_putendl_fd(input_line, fd[1]);
		free(input_line);
		input_line = readline(">");
	}
	close(fd[1]);
	rcmd->fd = fd[0];
	return (0);
}
