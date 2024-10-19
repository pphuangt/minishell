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

static int	check_second_arg(char *arg)
{
	int	i;
	int	ret;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	ret = ft_atoi(arg) % 256;
	if (ret < 0)
		ret = 256 + ret;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
		return (err_msg(0, "numeric argument required"), 2);
	else
		return (ret);
}

static int	get_argv_len(char **argv)
{
	int	ret;

	ret = 0;
	while (argv[ret])
		ret++;
	return (ret);
}

int	ft_exit(char **argv, t_shell *shell,
	int fd[2], int fd_size)
{
	int	argc;

	argc = get_argv_len(argv);
	if (argc == 2)
		shell->exit_status = check_second_arg(argv[1]);
	else if (argc > 2)
	{
		shell->exit_status = check_second_arg(argv[1]);
		if (shell->exit_status != 2)
			return (err_msg(0, "too many arguments"), 1);
	}
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
	free_environ(&shell->environ);
	close_fd(fd, fd_size);
	printf("exit\n");
	exit(shell->exit_status);
}
