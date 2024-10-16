/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:37 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 09:26:07 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_update_pwd(char *new_pwd, t_environ *environ)
{
	char	*pwd;

	pwd = get_variable_environ(environ->p, "PWD", 3);
	free(pwd);
	pwd = ft_strdup(new_pwd);
}

int	ft_change_dir(char *path, t_environ *environ)
{
	char	*pwd;
	char	*buff;

	if (!chdir(path))
	{
		return (1);//dir error
	}
	pwd = getcwd(buff, PATH_MAX);
	ft_update_pwd(pwd, environ);
	return (0);
}

int	ft_cd(char **argv, int argc, t_environ *environ)
{
	if (argc > 2)
	{
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	return (ft_change_dir(argv[1], environ));
}
