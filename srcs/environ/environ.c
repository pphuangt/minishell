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

static int	is_valid_format(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

static int	create_pointer_environ(t_environ *shell_environ, char **environ)
{
	size_t	size;

	size = 0;
	while (*environ)
	{
		if (is_valid_format(*environ))
			size++;
		environ++;
	}
	shell_environ->size = size * 2;
	shell_environ->p = malloc(sizeof(char *) * (shell_environ->size + 1));
	if (!shell_environ->p)
		return (err_ret("malloc"), 0);
	return (1);
}

static int	set_shlvl(t_environ *environ)
{
	char	*shlvl;
	int		value;
	char	*str;
	char	*var;

	shlvl = get_variable_environ(0, "SHLVL", 5);
	if (!shlvl)
		return (append_environ("SHLVL=1", environ));
	value = ft_atoi(shlvl);
	if (value < 0)
		return (handle_var_export("SHLVL=0", environ));
	value++;
	str = ft_itoa(value);
	if (!str)
		return (err_ret("malloc"), 0);
	var = ft_strjoin("SHLVL=", str);
	if (!var)
		return (free(str), err_ret("malloc"), 0);
	if (!handle_var_export(var, environ))
		return (free(str), free(var), 0);
	return (free(str), free(var), 1);
}

int	init_environ(t_environ *shell_environ)
{
	extern char	**environ;
	char		**envp;
	size_t		size;

	if (!create_pointer_environ(shell_environ, environ))
		return (-1);
	envp = environ;
	size = 0;
	while (*envp)
	{
		if (is_valid_format(*envp))
		{
			shell_environ->p[size] = ft_strdup(*envp);
			if (!shell_environ->p[size++])
				return (free_environ(shell_environ), err_ret("malloc"), -1);
		}
		envp++;
	}
	shell_environ->len = size;
	shell_environ->p[shell_environ->len] = NULL;
	get_variable_environ(shell_environ->p, 0, 0);
	if (!set_shlvl(shell_environ))
		return (-1);
	return (0);
}
