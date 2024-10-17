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

char	**get_sorted_env(t_environ *environ)
{
	char	**sorted_env;
	char	**p;
	int		i;

	sorted_env = malloc(sizeof(char *) * (environ->len + 1));
	p = environ->p;
	i = 0;
	while (i < environ->len)
	{
		while (p)
		{

		}
	}
}

void	export_env(t_environ *environ)
{
	char	**sorted_env;
	int		len;

	len = environ->len;
	sorted_env = get_sorted_env(environ);
	while (len > 0)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(sorted_env[environ->len - len], STDOUT_FILENO);
		len--;
	}
}

char	*get_path_name(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(str + i) != NULL && *(str + i) != '=')
		i++;
	tmp = malloc(sizeof(char) * i);
	ft_strlcpy(tmp, str, i);
	return (tmp);
}

int	set_data(char *p_update, char *data)
{
	if (p_update != NULL && data != NULL)
	{
		free(p_update);
		p_update = ft_strdup(data);
		free(data);
	}
	else if (data != NULL)
	{
		p_update = ft_strdup(data);
		free(data);
	}
	return (SUCCESS);
}


int	ft_export(char **argv, int argc, t_environ *environ)
{
	int		i;
	char	*pn;
	char	*tmp;

	i = 1;
	if (argc > 1)
	{
		while (argv[i] != NULL)
		{
			pn = get_path_name(argv[i]);
			tmp = get_variable_environ(environ, pn, ft_strlen(pn));
			if (tmp == NULL)
				add_variable_environ(environ, argv[i]);
			else
			{
				set_data(tmp, get_variable_environ(argv, pn, ft_strlen(pn)));
				free(tmp);
			}
			free(pn);
			i++;
		}
	}
	else
		export_env(environ);
	return (SUCCESS);
}
