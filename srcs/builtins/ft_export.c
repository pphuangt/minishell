/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:05:00 by paradari          #+#    #+#             */
/*   Updated: 2024/10/16 19:05:01 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_variable_environ(t_environ *environ, char *var)
{
	char	**p;
	char	**n_environ;

	if (environ->len == environ->size)
	{
		environ->size *= 2;
		n_environ = malloc(sizeof(char *) * (environ->size + 1));
		if (!n_environ)
			return ();
		ft_memcpy(n_environ, environ->p, sizeof(char *) * environ->len)
		free(environ->p);
		environ->p = n_environ;
	}
	environ->p[environ->len] = ft_strdup(var);
	environ->p[environ->len + 1] = NULL;
	return (SUCCESS);
}

int	ft_export(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	return(SUCCESS);
}
