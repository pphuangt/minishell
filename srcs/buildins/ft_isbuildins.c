/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:28 by paradari          #+#    #+#             */
/*   Updated: 2024/10/04 16:26:39 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isbuildins(t_cmd *cmd, t_execcmd *ecmd)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(ecmd->argv, "echo", 5) == 0)
		ret = ft_echo(cmd);
	else if (ft_strncmp(ecmd->argv, "cd", 3) == 0)
		ret = ft_cd(cmd);
	else if (ft_strncmp(ecmd->argv, "pwd", 4) == 0)
		ret = ft_pwd(pwd);
	else if (ft_strncmp(ecmd->argv, "export", 7) == 0)
		ret = ft_export(cmd);
	else if (ft_strncmp(ecmd->argv, "unset", 6) == 0)
		ret = ft_unset(cmd);
	else if (ft_strncmp(ecmd->argv, "env", 4) == 0)
		ret = ft_env(cmd, environ);
	else if (ft_strncmp(ecmd->argv, "exit", 5) == 0)
		ret = ft_exit(cmd);
	return (ret);
}
