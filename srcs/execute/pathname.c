/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:51:42 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/30 18:51:49 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_pathname_error(char *cmd_name, t_shell *shell)
{
	err_ret("malloc");
	free(cmd_name);
	clean_and_exit(shell, SYSTEM_ERROR);
}

static char	*search_from_path_variable(char *cmd_name, char *path_varaible,
		t_shell *shell)
{
	char	**split_path;

	split_path = ft_split(path_variable, ':');
	if (!split_path)
		search_pathname_error(cmd_name, shell);
}

char	*search_pathname(char *cmd_name, t_shell *shell)
{
	char	*path_variable;
	char	*ret;

	path_variable = get_variable_environ(NULL, "PATH", 4);
	if (!path_variable || !*path_variable)
	{
		ret = ft_strjoin("./", cmd_name);
		if (!ret)
			search_pathname_error(cmd_name, shell);
	}
	else
		ret = search_in_path_variable(cmd_name, path_variable, shell);
	free(cmd_name);
	return (ret);
}
