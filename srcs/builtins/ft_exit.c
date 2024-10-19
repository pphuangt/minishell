/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:11 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 16:09:22 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, int fd[2], int fd_size)
{
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
	free_environ(&shell->environ);
	close_fd(fd, fd_size);
	printf("exit\n");
	exit(shell->exit_status);
}
