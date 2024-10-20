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
			return (1);
	}
	return (0);
}

int	is_pathname_exist(char **pathname, char *cmd_name)
{
	char	*tmp;

	if (!*pathname)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (access(*pathname, F_OK) != 0 && errno != ENOTDIR)
		err_ret(cmd_name);
	else
		return (1);
	tmp = *pathname;
	*pathname = NULL;
	free(tmp);
	return (0);
}

void	on_execve_error(char **pathname, t_shell *shell,
		int	*fd, int fd_size)
{
	int		error;
	char	*tmp;

	error = errno;
	if (error == ENOEXEC)
	{
		ft_putstr_fd(*pathname, STDERR_FILENO);
		ft_putstr_fd(": cannot execute file: ", STDERR_FILENO);
		ft_putendl_fd(strerror(ENOEXEC), STDERR_FILENO);
	}
	else if (is_dir(*pathname))
		err_msg(EISDIR, *pathname);
	else
		err_ret(*pathname);
	tmp = *pathname;
	*pathname = NULL;
	free(tmp);
	clean_and_exit(shell, CMD_NOT_EXEC, fd, fd_size);
}

void	clean_and_exit(t_shell *shell, int exit_status,
	int *fd, int fd_size)
{
	freecmd(shell->cmd);
	free_environ(&shell->environ);
	free(shell->input);
	rl_clear_history();
	close_fd(fd, fd_size);
	exit(exit_status);
}
