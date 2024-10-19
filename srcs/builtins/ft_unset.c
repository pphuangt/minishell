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

int	remove_variable_environ(t_environ *environ, char *name, size_t size)
{
	char	**p;

	p = environ->p;
	while (*p)
	{
		if (ft_strncmp(*p, name, size) == 0 && *(*p + size) == '=')
		{
			free(*p);
			while (*(p + 1) != NULL)
			{
				*p = *(p + 1);
				p++;
			}
			p = NULL;
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
