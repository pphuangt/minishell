/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:05:21 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/15 18:05:28 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std_fd(int *std_in, int *std_out, int *std_err)
{
	*std_in = dup(STDIN_FILENO);
	if (*std_in == -1)
		return (err_ret("dup"), -1);
	*std_out = dup(STDOUT_FILENO);
	if (*std_out == -1)
		return (close(*std_in), err_ret("dup"), -1);
	*std_err = dup(STDERR_FILENO);
	if (*std_err == -1)
		return (close(*std_in), close(*std_out), err_ret("dup"), -1);
	return (SUCCESS);
}

int	restore_std_fd(int *std_in, int *std_out, int *std_err)
{
	int	ret;

	ret = SUCCESS;
	if (dup2(*std_in, STDIN_FILENO) < 0
		|| dup2(*std_out, STDOUT_FILENO) < 0
		|| dup2(*std_err, STDERR_FILENO) < 0)
	{
		err_ret("dup2");
		ret = SYSTEM_ERROR;
	}
	close(*std_in);
	close(*std_out);
	close(*std_err);
	*std_in = -1;
	*std_out = -1;
	*std_err = -1;
	return (ret);
}

int	is_new_fd(int new_fd, int fd[], int fd_size)
{
	int	i;

	i = 0;
	while (i < fd_size)
	{
		if (fd[i++] == new_fd)
			return (0);
	}
	return (1);
}

void	close_fd(int fd[], int fd_size)
{
	int	i;

	i = -1;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	while (++i < fd_size)
	{
		if (fd[i] == STDIN_FILENO
			|| fd[i] == STDOUT_FILENO
			|| fd[i] == STDOUT_FILENO)
			continue ;
		close(fd[i]);
	}
}
