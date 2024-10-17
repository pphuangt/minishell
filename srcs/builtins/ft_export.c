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

char	*get_next_node(t_environ *environ, int len)
{
	int		i;
	int		j;
	char	**p;

	i = 0;
	j = 0;
	p = environ->p;
	while (*p[i])
	{
		while (*p[i] <= *p[j])
	}
}

void	export_env(t_environ *environ)
{
	int		len;
	char	*next;

	len = environ->len;
	while (len > 0)
	{
		next = get_next_node(environ, len);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(next, STDOUT_FILENO);
		len--;
		free(next);
	}
}

int	ft_export(char **argv, int argc, t_environ *environ)
{
	int	i;

	i = 1;
	(void)argv;
	(void)argc;
	(void)environ;
	if (argc > 1)
	{
		while (argv[i] != NULL)
		{
			add_variable_environ(environ, argv[i]);
			i++;
		}
	}
	else
		export_env(environ);
	return (SUCCESS);
}
