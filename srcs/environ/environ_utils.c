/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:07:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/20 19:07:55 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_environ(char *str, t_environ *environ)
{
	char	**p;
	char	*n_str;

	if (environ->len == environ->size)
	{
		environ->size *= 2;
		p = malloc(sizeof(char *) * (environ->size + 1));
		if (!p)
			return (err_ret("malloc"), 0);
		ft_memcpy(p, environ->p, sizeof(char *) * environ->len);
		free(environ->p);
		environ->p = p;
	}
	n_str = ft_strdup(str);
	if (!n_str)
		return (err_ret("malloc"), 0);
	environ->p[environ->len] = n_str;
	environ->len++;
	environ->p[environ->len] = NULL;
	return (1);
}
