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

static void	print_err_cd(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

static int	go_back_path(char *old_pwd, char *last_pwd)
{
	if (old_pwd)
	{
		(void)last_pwd;
		if (chdir(old_pwd) == -1)
		{
			print_err_cd(old_pwd);
			return (0);
		}
		ft_putendl_fd(old_pwd, STDOUT_FILENO);
	}
	else
	{
		if (chdir(last_pwd) == -1)
		{
			print_err_cd(last_pwd);
			return (0);
		}
		ft_putendl_fd(last_pwd, STDOUT_FILENO);
	}
	return (1);
}

static int	ft_change_dir(char *path, t_environ *environ)
{
	char		*pwd;
	char		buff[MAXLINE];
	char		*old_pwd;
	static char	last_pwd[MAXLINE];

	if (!path || !ft_strncmp(path, "~", ft_strlen(path)))
		chdir(get_variable_environ(0, "HOME", 4));
	else if (!ft_strncmp(path, "-", ft_strlen(path)))
	{
		if (!go_back_path(get_variable_environ(0, "OLDPWD", 6), last_pwd))
			return (1);
	}
	else if (chdir(path) == -1)
	{
		print_err_cd(path);
		return (1);
	}
	old_pwd = get_variable_environ(0, "PWD", 3);
	if (!old_pwd)
		old_pwd = last_pwd;
	ft_update_wd(old_pwd, environ, 0);
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
