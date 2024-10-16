/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <paradari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:25:53 by paradari          #+#    #+#             */
/*   Updated: 2024/10/12 09:53:24 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isflag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (i == 2)
			return (1);
	}
	return (0);
}

void	ft_print_argv(char **argv, int i, int flag)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(char **argv, int argc)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && ft_isflag(argv[i]) && argc > 0)
	{
		flag = 1;
		i++;
		argc--;
	}
	ft_print_argv(argv, i, flag);
	return (0);
}