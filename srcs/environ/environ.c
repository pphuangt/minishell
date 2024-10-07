/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:29:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/27 19:29:47 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_environ(char *str, size_t size)
{
	extern char	**environ;
	char		**env;

	env = environ;
	if (!str || size == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, str, size) == 0 && *(*env + size) == '=')
			return (*env + size + 1);
		env++;
	}
	return (NULL);
}
