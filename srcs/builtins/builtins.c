/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:14:24 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 16:14:26 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run cd\n");
	return (0);
}

int	ft_pwd(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run pwd\n");
	return (0);
}

int	ft_export(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run export\n");
	return (0);
}

int	ft_unset(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run unset\n");
	return (0);
}

int	ft_env(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run env\n");
	return (0);
}
