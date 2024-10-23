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

static int	read_heredoc(t_redircmd *rcmd, t_shell *shell,
		int has_q, int fd)
{
	t_shell	hd_shell;
	char	*s;
	int		exit_status;

	init_shell(&hd_shell);
	exit_status = shell->exit_status;
	shell->exit_status = 0;
	while (rl_gets(&hd_shell, &s, "> ", 0))
	{
		if (shell->exit_status == TERM_BY_SIG + SIGINT)
			return (free(s), -1);
		if (ft_strcmp(s, rcmd->file.s) == 0)
			break ;
		if (has_q)
			ft_putendl_fd(s, fd);
		else if (put_heredoc_fd(s, fd, exit_status) < 0)
			return ((shell->exit_status = 1), free(s), close(fd), -1);
		free(s);
	}
	if (!s)
		end_by_eof_msg(rcmd->file.s, shell->count_line);
	shell->count_line += hd_shell.count_line - 1;
	return ((shell->exit_status = exit_status), free(s), close(fd), 1);
}

int	heredoc(t_redircmd *rcmd, t_shell *shell)
{
	int		fd;
	char	*str;
	char	has_q;

	fd = setup_hd_file(rcmd);
	if (fd < 0)
		return ((shell->exit_status = SYSTEM_ERROR), -1);
	has_q = 0;
	if (ft_strchr(rcmd->file.s, '\'') || ft_strchr(rcmd->file.s, '\"'))
		has_q = 1;
	str = ft_strdup(rcmd->file.s);
	if (!str)
		return ((shell->exit_status = SYSTEM_ERROR),
			err_ret("malloc here document"), close(fd), -1);
	if (has_q)
		strip_quotes(str);
	rcmd->file.s = str;
	rcmd->file.e = str;
	return (read_heredoc(rcmd, shell, has_q, fd));
}
