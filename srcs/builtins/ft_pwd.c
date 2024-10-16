/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:47 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 10:09:23 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv, int argc, t_environ *environ)
{
	char	*wd;
	char	buff[MAXLINE];

	(void)argv;
	(void)argc;
	(void)environ;
	wd = getcwd(buff, MAXLINE);
	if (wd)
		ft_putendl_fd(wd, STDOUT_FILENO);
	return (0);
}