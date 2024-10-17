/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:38:53 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/16 21:39:02 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environ(t_environ *environ)
{
	char	**envp;

	envp = environ->p;
	while (*envp)
		free(*envp++);
	free(environ->p);
	environ->p = NULL;
}
