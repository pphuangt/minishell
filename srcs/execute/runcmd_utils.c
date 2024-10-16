/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:33:39 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 23:33:45 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *dir)
{
	struct stat	path_stat;

	if (access(dir, F_OK) != -1)
	{
		stat(dir, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
			return (0);
	}
	return (1);
}

int	is_pathname_exist(char *pathname, char *cmd_name)
{
	if (!pathname)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (access(pathname, F_OK) != 0 && errno != ENOTDIR)
		err_ret(pathname);
	else
		return (1);
	return (0);
}

void	on_execve_error(t_shell *shell, char *pathname)
{
	int	error;

	error = errno;
	if (error == ENOEXEC)
	{
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": cannot execute file: ", STDERR_FILENO);
		ft_putendl_fd(strerror(ENOEXEC), STDERR_FILENO);
	}
	else if (is_dir(pathname))
		err_msg(EISDIR, pathname);
	else
		err_ret(pathname);
	clean_and_exit(shell, pathname, CMD_NOT_EXEC);
}

void	clean_and_exit(t_shell *shell, char *pathname, int exit_status)
{
	freecmd(shell->cmd);
	free_environ(&shell->environ);
	free(shell->input);
	free(pathname);
	exit(exit_status);
}