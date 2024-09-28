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

static void	end_heredoc(char *input_line, char *delimiter, size_t count_line)
{
	if (!input_line)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
		ft_putnbr_fd((int)count_line, STDERR_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
	else
		free(input_line);
}

static int	put_heredoc_fd(char *input_line, int fd, int has_q)
{
	char	*str;

	if (has_q)
		ft_putendl_fd(input_line, fd);
	else
	{
		str = expand_env_var(input_line);
		if (!str)
		{
			free(input_line);
			err_ret("malloc expand heredoc");
			return (-1);
		}
		ft_putendl_fd(str, fd);
		free(str);
	}
	free(input_line);
	return (0);
}

static int	read_heredoc(t_shell *shell, t_redircmd *rcmd, int has_q)
{
	int			fd[2];
	char		*input_line;
	size_t		count_line;

	if (pipe(fd) == -1)
		return (err_ret("pipe"), -1);
	count_line = shell->count_line;
	input_line = readline(">");
	while (input_line)
	{
		shell->count_line++;
		if (shell->exit_status != 0)
			return (free(input_line), -1);
		if (ft_strncmp(input_line, rcmd->file.s, -1) == 0)
			break ;
		if (put_heredoc_fd(input_line, fd[1], has_q) < 0)
			return (-1);
		input_line = readline(">");
	}
	end_heredoc(input_line, rcmd->file.s, count_line);
	close(fd[1]);
	rcmd->fd = fd[0];
	return (0);
}

int	heredoc(t_shell *shell, t_redircmd *rcmd)
{
	char	*str;
	char	has_q;

	has_q = 0;
	if (ft_strchr(rcmd->file.s, '\'') || ft_strchr(rcmd->file.s, '\"'))
		has_q = 1;
	str = ft_strdup(rcmd->file.s);
	if (!str)
	{
		err_ret("malloc here document");
		return (-1);
	}
	if (has_q)
		strip_matching_quotes(str);
	rcmd->file.s = str;
	rcmd->file.e = str;
	if (read_heredoc(shell, rcmd, has_q) < 0)
		return (-1);
	return (0);
}
