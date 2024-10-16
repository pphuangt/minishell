/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_uf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:55 by paradari          #+#    #+#             */
/*   Updated: 2024/10/04 16:26:56 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_unset_node(char	**node)
{

}

int	remove_variable_environ(t_environ *environ, char *name, size_t size)
{
	char	**p;
	char	**tmp;

	p = environ->p;
	**tmp = malloc(sizeof(char *) * (environ->len));
	while (*p)
	{
		if (ft_strncmp(*p, name, size) == 0 && *(*p + size) == '=')
		{
			free(*p)
			while (*(p + 1))
			{
				*p = *(p + 1)
				p++;
			}
			*p = NULL;
			environ->len--;
			break;
		}
		p++;
	}
	return (0);
}


int	ft_unset(char **argv)
{
	extern char	**environ;
	char		**node_to_unset;
	int			i;

	i = 0;
	while (argv[i])
	{
		node_to_unset = get_variable_environ(argv[i], ft_strlen(argv[i]));
		ft_unset_node(node_to_unset);
		i++;
	}
	return (0);
}
