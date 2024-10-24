/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:55 by paradari          #+#    #+#             */
/*   Updated: 2024/10/04 16:26:56 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_variable_environ(t_environ *environ,
		char *key, size_t key_len)
{
	char		**p;

	p = environ->p;
	while (*p)
	{
		if (ft_strncmp(*p, key, key_len) == 0
			&& (*(*p + key_len) == '=' || *(*p + key_len) == '\0'))
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

int	ft_unset(char **argv, int argc, t_environ *environ)
{
	int	i;

	i = 1;
	while (argv[i] != NULL && argc > 1)
	{
		remove_variable_environ(environ, argv[i], ft_strlen(argv[i]));
		i++;
	}
	return (0);
}
