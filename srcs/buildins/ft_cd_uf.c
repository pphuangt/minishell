/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_uf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:37 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 09:26:07 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_change_pwd(char *new_pwd, t_environ *environ)
{
	char	*pwd;

	pwd = get_variable_environ(environ->p, "PWD", 3);
	//free_old_pwd
	//...
	pwd = ft_strdup(new_pwd);
}

int	ft_change_dir(char *path, t_environ *environ)
{
	char	*pwd;
	char	*buff;

	if (!chdir(path))
		return ();//dir error
	pwd = getcwd(buff, 4242); //test
	if (!ret)
	{
		//get_pwd_from_struct_and_join_new_path
	}
	ft_change_pwd(pwd, environ);
	return (0);
}

int	ft_cd(char **argv, t_environ *environ)
{
	//check arg
	if (argv[2])
	{
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
		return ();
	}
	//check dir
	// if (check_exit)
	// {
	// 	ft_putstr_fd("No such file or directory\n", STDOUT_FILENO);
	// 	return ();
	// }
	// if (is_dir)
	// {
	// 	ft_putstr_fd("Not a directory\n", STDOUT_FILENO);
	// 	return ();
	// }
	//change path && pwd
	return (ft_change_dir(argv[1], environ));
}