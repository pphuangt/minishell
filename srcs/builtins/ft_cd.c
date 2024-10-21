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

#include "minishell.h"

int	handle_var_export(char *str, t_environ *environ);

static void	ft_update_wd(char *new_wd, t_environ *environ, int i)
{
	char	*wd;

	if (i)
		wd = ft_strjoin("PWD=", new_wd);
	else
		wd = ft_strjoin("OLDPWD=", new_wd);
	handle_var_export(wd, environ);
	free(wd);
}

static int	ft_change_dir(char *path, t_environ *environ)
{
	char		*pwd;
	char		buff[MAXLINE];
	char		*old_pwd;
	static char	last_pwd[MAXLINE];

	old_pwd = get_variable_environ(0, "PWD", 3);
	if (!old_pwd)
		old_pwd = ft_strdup(last_pwd);
	ft_update_wd(old_pwd, environ, 0);
	if (!path)
		chdir(get_variable_environ(0, "HOME", 4));
	else if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	pwd = getcwd(buff, MAXLINE);
	ft_update_wd(pwd, environ, 1);
	ft_strlcpy(last_pwd, pwd, ft_strlen(pwd) + 1);
	return (0);
}

int	ft_cd(char **argv, int argc, t_environ *environ)
{
	if (argc > 2)
		return (err_msg(0, "cd: too many arguments"), 1);
	return (ft_change_dir(argv[1], environ));
}
