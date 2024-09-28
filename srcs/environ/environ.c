/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:29:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/27 19:29:47 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_shell *shell)
{
	char	**envp;

	envp = shell->environ.p;
	while (*envp)
	{
		free(*envp);
		envp++;
	}
	free(shell->environ.p);
}

char	*get_variable_environ(char *str, size_t size)
{
	extern char	**environ;
	char		**env;

	env = environ;
	if (!str || size == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, str, size) == 0 && *(*env + size) == '=')
			return (*env + size + 1);
		env++;
	}
	return (NULL);
}

int	add_variable_environ(t_shell *shell, char *var)
{
	char		**n_environ;
	t_environ	*environ;

	environ = &shell->environ;
	if (environ->len == environ->size)
	{
		environ->size = environ->size * 2;
		n_environ = malloc(sizeof(char *) * (environ->size + 1));
		if (!n_environ)
			return (err_ret("malloc"), -1);
		ft_memcpy(n_environ, environ->p, sizeof(char *) * environ->len);
		free(environ->p);
		environ->p = n_environ;
	}
	var = ft_strdup(var);
	if (!var)
		return (err_ret("malloc"), -1);
	environ->p[environ->len++] = var;
	environ->p[environ->len] = NULL;
	return (0);
}

int	remove_variable_environ(t_shell *shell, char *name, size_t size)
{
	t_environ	*environ;
	char		**p;

	environ = &shell->environ;
	p = environ->p;
	while (*p)
	{
		if (ft_strncmp(*p, name, size) == 0 && *(*p + size) == '=')
		{
			free(*p);
			while (*(p + 1))
			{
				*p = *(p + 1);
				p++;
			}
			*p = NULL;
			environ->len--;
			break ;
		}
		p++;
	}
	return (0);
}

int	init_environ(t_shell *shell)
{
	extern char	**environ;
	size_t		size;
	char		**envp;

	size = 0;
	envp = environ;
	while (*envp && ++size)
		envp++;
	shell->environ.size = size * 2;
	shell->environ.p = malloc(sizeof(char *) * (shell->environ.size + 1));
	if (!shell->environ.p)
		return (err_ret("malloc"), -1);
	envp = environ;
	size = 0;
	while (*envp)
	{
		shell->environ.p[size] = ft_strdup(*envp);
		if (!shell->environ.p[size++])
			return (free_envp(shell), err_ret("malloc"), -1);
		envp++;
	}
	shell->environ.len = size;
	shell->environ.p[shell->environ.len] = NULL;
	environ = shell->environ.p;
	return (0);
}
