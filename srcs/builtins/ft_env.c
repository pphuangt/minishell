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

int	ft_env(t_environ *environ)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	env = environ->p;
	if (!env)
		return (1);
	while (env[i])
	{
		j = 0;
		while (ft_isalnum(env[i][j]) || env[i][j] == '_')
			j++;
		if (env[i][j] == '=')
			ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
