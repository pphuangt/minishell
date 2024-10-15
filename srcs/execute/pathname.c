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

static void	free_split(char **p)
{
	char	**head;

	head = p;
	while (*p)
	{
		free(*p);
		p++;
	}
	free(head);
}

char	*search_pathname(char *name, size_t len)
{
	char	**path;
	char	**curr;
	char	*pathname;
	size_t	path_len;

	path = ft_split(get_variable_environ(NULL, "PATH", 4), ':');
	if (!path)
		return (NULL);
	curr = path;
	while (*curr)
	{
		path_len = ft_strlen(*curr);
		pathname = malloc(sizeof(char) * (path_len + len + 2));
		if (!pathname)
			return (free_split(path), err_ret("malloc"), NULL);
		ft_memcpy(pathname, *curr, path_len);
		pathname[path_len] = '/';
		ft_memcpy(pathname + path_len + 1, name, path_len + len + 2);
		pathname[path_len + len + 1] = '\0';
		if (access(pathname, X_OK) == 0)
			return (free_split(path), pathname);
		free(pathname);
		curr++;
	}
	return (free_split(path), NULL);
}
