/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_pathname.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:32:11 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/17 20:32:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exec_pathname(char **pathname, t_shell *shell)
{
	char	*s;
	char	*path;

	s = *pathname;
	path = get_variable_environ(NULL, "PATH", 4);
	if (!path || !*path)
	{
		*pathname = ft_strjoin("./", s);
		return (free(s), *pathname != NULL);
	}
}
