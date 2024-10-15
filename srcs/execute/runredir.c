/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:30:53 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/15 17:31:00 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	runredir(t_redircmd *rcmd, t_shell *shell)
{
	int	fd;

	if (rcmd->mode == O_DSYNC)
	{
		if (heredoc(rcmd, shell) < 0)
			return (SYSTEM_ERROR);
	}
	else
	{
		fd = open(rcmd->file.s, rcmd->mode);
		if (fd < 0)
			return (err_ret("open"), SYSTEM_ERROR);
		if (dup2(fd, rcmd->fd) < 0)
			return (close(fd), err_ret("dup2"), SYSTEM_ERROR);
		if (fd != rcmd->fd)
			close(fd);
	}
	return (SUCCESS);
}
