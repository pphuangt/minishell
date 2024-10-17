/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:09:11 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 16:09:22 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_second_arg(char *arg)
{
	int	i;

	i = 0;
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i]))
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
	{
		ft_putendl_fd("numeric argument required", STDOUT_FILENO);
		return (2);
	}
	else
		return (ft_atoi(argv[1]) % 256);
}

int	ft_exit(char *argv, int argc, t_shell *shell)
{
	if (argc == 2)
		shell->exit_status = check_second_arg(argv[1]);
	else if (argc > 2)
	{
		shell->exit_status = check_second_arg(argv[1]);
		if (shell->exit_status != 2)
		{
			ft_putendl_fd("too many arguments", STDOUT_FILENO);
			return (1);
		}
	}
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
	free_environ(&shell->environ);
	printf("exit\n");
	exit(shell->exit_status);
}
