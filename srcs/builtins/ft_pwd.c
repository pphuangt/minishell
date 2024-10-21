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

int	ft_pwd(void)
{
	char	*wd;
	char	buff[MAXLINE];

	wd = getcwd(buff, MAXLINE);
	if (!wd)
		wd = get_variable_environ(0, "PWD", 3);
	ft_putendl_fd(wd, STDOUT_FILENO);
	return (0);
}
