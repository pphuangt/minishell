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

int	remove_variable_environ(t_environ *environ, char *name, size_t size)
{
	char	**p;
	char	**tmp;
	int		i;
	int		len;

	len = environ->len;
	p = environ->p;
	**tmp = malloc(sizeof(char *) * (environ->size));
	while (*p)
	{
		if (ft_strncmp(*p, name, size) == 0 && *(*p + size) == '=')
		{
			p++;
			environ->len--;
		}
		*tmp = ft_strdup(*p);
		tmp++;
		p++;
	}
	if (len > environ->len)
	{
		while (*p)
		{
			free(*p);
			p++;
		}
		free(p);
		p = tmp;
	}
	else
	{
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(tmp);
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
