/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:24:15 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/02 08:24:18 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_doit(int error, const char *fmt)
{
	char	buff[MAXLINE];

	if (fmt)
		ft_strlcpy(buff, fmt, MAXLINE);
	if (error)
	{
		ft_strlcat(buff, ": ", MAXLINE - 1);
		ft_strlcat(buff, strerror(error), MAXLINE - 1);
	}
	ft_strlcat(buff, "\n", MAXLINE - 1);
	ft_putstr_fd(buff, STDERR_FILENO);
}

void	err_ret(const char *fmt)
{
	err_doit(errno, fmt);
}

void	err_sys(const char *fmt)
{
	err_doit(errno, fmt);
	exit(1);
}

void	err_msg(int error, const char *fmt)
{
	err_doit(error, fmt);
}

void	err_exit(int error, const char *fmt)
{
	err_doit(error, fmt);
	exit(1);
}
