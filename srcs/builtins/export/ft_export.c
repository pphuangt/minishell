/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:10:44 by paradari          #+#    #+#             */
/*   Updated: 2024/10/20 18:10:46 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_exported_env(t_environ *environ);
void	print_err_msg(char *str);
char	*extract_key(char *str);

static int	is_key_in_environ(char *key, t_environ *environ)
{
	char	**p;
	size_t	key_len;
	int		i;

	p = environ->p;
	key_len = ft_strlen(key);
	i = 0;
	while (p[i])
	{
		if (!ft_strncmp(p[i], key, key_len) && p[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	handle_var_export(char *str, t_environ *environ)
{
	char	*key;
	char	*n_str;
	int		i;

	key = extract_key(str);
	if (!key)
		return (0);
	i = is_key_in_environ(key, environ);
	if (i >= 0)
	{
		n_str = ft_strdup(str);
		if (!n_str)
			return (err_ret("malloc"), 0);
		free(environ->p[i]);
		environ->p[i] = n_str;
		free(key);
	}
	else
	{
		free(key);
		if (!append_environ(str, environ))
			return (0);
	}
	return (1);
}

int	ft_export(char **argv, int argc, t_environ *environ)
{
	int	ret;
	int	i;

	if (argc < 2)
		return (print_exported_env(environ));
	ret = SUCCESS;
	i = 1;
	while (argv[i])
	{
		if (!is_valid_varname(argv[i]))
		{
			print_err_msg(argv[i]);
			ret = SYSTEM_ERROR;
		}
		else if (!handle_var_export(argv[i], environ))
			return (SYSTEM_ERROR);
		i++;
	}
	return (ret);
}
