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

static void	end_by_eof_msg(char *delimiter, int count_line)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(count_line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static int	end_heredoc(t_shell *hd_shell, size_t *count_line,
		int hd_fd, int fd[2])
{
	*count_line += hd_shell->count_line - 1;
	close(fd[1]);
	if (dup2(fd[0], hd_fd) == -1)
		return (close(fd[0]), err_ret("dup2"), -1);
	if (fd[0] != hd_fd)
		close(fd[0]);
	return (0);
}

static int	put_heredoc_fd(char *s, int fd, int exit_status)
{
	char	*str;

	str = expand_env_var(s, exit_status, 1);
	if (!str)
		return (err_ret("malloc expand heredoc"), -1);
	ft_putendl_fd(str, fd);
	free(str);
	return (0);
}

static int	read_heredoc(t_redircmd *rcmd, t_shell *shell, int has_q)
{
	t_shell	hd_shell;
	int		fd[2];
	char	*s;
	size_t	file_len;

	if (pipe(fd) == -1)
		return (err_ret("pipe"), -1);
	init_shell(&hd_shell);
	file_len = ft_strlen(rcmd->file.s);
	while (rl_gets(&hd_shell, &s, "> ", 0))
	{
		if (ft_strncmp(s, rcmd->file.s, file_len) == 0)
			break ;
		if (has_q)
			ft_putendl_fd(s, fd[1]);
		else if (put_heredoc_fd(s, fd[1], shell->exit_status) < 0)
			return (free(s), close(fd[0]), close(fd[1]), -1);
		free(s);
	}
	if (!s)
		end_by_eof_msg(rcmd->file.s, shell->count_line);
	return (free(s), end_heredoc(&hd_shell, &shell->count_line, rcmd->fd, fd));
}

int	heredoc(t_redircmd *rcmd, t_shell *shell)
{
	char	*str;
	char	has_q;

	has_q = 0;
	if (ft_strchr(rcmd->file.s, '\'') || ft_strchr(rcmd->file.s, '\"'))
		has_q = 1;
	str = ft_strdup(rcmd->file.s);
	if (!str)
		return (err_ret("malloc here document"), -1);
	if (has_q)
		strip_quotes(str);
	rcmd->file.s = str;
	rcmd->file.e = str;
	if (read_heredoc(rcmd, shell, has_q) < 0)
		return (-1);
	return (0);
}
