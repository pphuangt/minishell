/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:01 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 10:03:10 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_env(char **argv, t_environ *environ)
{
	char	**env;
	int		i;

	i = 0;
	if (argv && argv[1])
		return (); //too many arg
	env = environ->p;
	if (!env)
		return (1);//not sure exit code
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}