/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:01 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 10:03:10 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **argv, int argc, t_environ *environ)
{
	char	**env;
	int		i;

	(void)argv;
	(void)argc;
	i = 0;
	env = environ->p;
	if (!env)
		return (1);
	while (env[i])
		ft_putendl_fd(env[i++], STDOUT_FILENO);
	return (0);
}
