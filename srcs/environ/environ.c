/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:29:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/02 09:13:20 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_environ(char **environ, char *str, size_t size)
{
	static char	**s_environ = NULL;
	char		**env;

	if (environ != NULL)
	{
		s_environ = environ;
		return (NULL);
	}
	env = s_environ;
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

int	init_environ(t_environ *shell_environ)
{
	extern char	**environ;
	size_t		size;
	char		**envp;

	size = 0;
	envp = environ;
	while (*envp && ++size)
		envp++;
	shell_environ->size = size * 2;
	shell_environ->p = malloc(sizeof(char *) * (shell_environ->size + 1));
	if (!shell_environ->p)
		return (err_ret("malloc"), -1);
	envp = environ;
	size = 0;
	while (*envp)
	{
		shell_environ->p[size] = ft_strdup(*envp);
		if (!shell_environ->p[size++])
			return (free_environ(shell_environ), err_ret("malloc"), -1);
		envp++;
	}
	shell_environ->len = size;
	shell_environ->p[shell_environ->len] = NULL;
	get_variable_environ(shell_environ->p, 0, 0);
	return (0);
}
