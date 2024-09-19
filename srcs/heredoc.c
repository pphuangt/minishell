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

static void	strip_matching_quotes(char *s)
{
	int		i;
	int		j;
	char	quote_status;

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

static int	put_heredoc_fd(char *input_line, int fd, int has_q, char **env)
{
	char	*str;

	if (has_q)
		ft_putendl_fd(input_line, fd);
	else
	{
		str = expand_heredoc(input_line, env);
		if (!str)
		{
			err_ret("malloc expand heredoc");
			return (-1);
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
	return (0);
}

static int	read_heredoc(t_redircmd *rcmd, int has_q, char **env)
{
	int			fd[2];
	char		*input_line;

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
		if (put_heredoc_fd(input_line, fd[1], has_q, env) < 0)
			return (-1);
		free(input_line);
		input_line = readline(">");
	}
	close(fd[1]);
	rcmd->fd = fd[0];
	return (0);
}

int	heredoc(t_redircmd *rcmd, char **env)
{
	char	*str;
	char	has_q;

	has_q = 0;
	if (ft_strchr(rcmd->file.s, '\'') || ft_strchr(rcmd->file.s, '\"'))
		has_q = 1;
	str = ft_strdup(rcmd->file.s);
	if (!str)
	{
		err_ret("here document");
		return (-1);
	}
	if (has_q)
		strip_matching_quotes(str);
	rcmd->file.s = str;
	rcmd->file.e = str;
	if (read_heredoc(rcmd, has_q, env) < 0)
		return (-1);
	return (0);
}
