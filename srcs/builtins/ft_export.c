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

int		print_err_msg(char *arg);
int		cmp_strings(char *str1, char *str2);
int		is_valid_path(char *arg);
char	*get_path_name(char *str);

static int	add_variable_environ(t_environ *environ, char *var)
{
	char	**n_environ;

	if (environ->len == environ->size)
	{
		environ->size *= 2;
		n_environ = malloc(sizeof(char *) * (environ->size + 1));
		if (!n_environ)
			return (1);
		ft_memcpy(n_environ, environ->p, sizeof(char *) * environ->len);
		free(environ->p);
		environ->p = n_environ;
	}
	environ->p[environ->len] = ft_strdup(var);
	environ->len++;
	environ->p[environ->len + 1] = NULL;
	return (SUCCESS);
}

static char	**get_sorted_env(t_environ *environ)
{
	char	**sorted;
	size_t	i;
	size_t	j;
	char	*tmp;

	sorted = malloc(sizeof(char *) * (environ->len + 1));
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < environ->len)
	{
		sorted[i] = ft_strdup(environ->p[i]);
		i++;
	}
	sorted[i] = NULL;
	i = 0;
	while (i < environ->len - 1)
	{
		j = 0;
		while (j < environ->len - i -1)
		{
			if (cmp_strings(environ->p[j], environ->p[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

static void	export_env(t_environ *environ)
{
	char	**sorted;
	int		len;
	char	*name;
	int		nlen;

	len = environ->len;
	sorted = get_sorted_env(environ);
	while (len > 0)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		name = get_path_name(sorted[environ->len - len]);
		nlen = ft_strlen(name);
		if (sorted[environ->len - len][nlen])
		{
			ft_putstr_fd(name, STDOUT_FILENO);
			sorted[environ->len - len] += nlen + 1;
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted[environ->len - len], STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(name, STDOUT_FILENO);
		len--;
	}
}

static int	set_data(char *p_update, char *data)
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
	int		ret;

	ret = 0;
	i = 0;
	if (argc > 1)
	{
		while (argv[++i])
		{
			pn = get_path_name(argv[i]);
			if (!is_valid_path(argv[i]))
				ret = print_err_msg(argv[i]);
			else
			{
				tmp = get_variable_environ(environ->p, pn, ft_strlen(pn));
				if (tmp == NULL)
					add_variable_environ(environ, argv[i]);
				else
					set_data(tmp, get_variable_environ(argv, pn, ft_strlen(pn)));
			}
			free(pn);
		}
	}
	else
		export_env(environ);
	return (ret);
}
