/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:18:28 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/15 22:18:34 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_redircmd *rcmd)
{
	int	fd;

	if (rcmd->mode == O_DSYNC)
	{
		if (dup2(rcmd->hd_fd, rcmd->fd) < 0)
			return (err_ret("dup2"), SYSTEM_ERROR);
		if (rcmd->hd_fd != rcmd->fd)
			close(rcmd->hd_fd);
	}
	else
	{
		if (rcmd->mode == O_RDONLY)
			fd = open(rcmd->file.s, rcmd->mode);
		else
			fd = open(rcmd->file.s, rcmd->mode,
					(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
		if (fd < 0)
			return (err_ret("open"), SYSTEM_ERROR);
		if (dup2(fd, rcmd->fd) < 0)
			return (close(fd), err_ret("dup2"), SYSTEM_ERROR);
		if (fd != rcmd->fd)
			close(fd);
	}
	return (SUCCESS);
}
