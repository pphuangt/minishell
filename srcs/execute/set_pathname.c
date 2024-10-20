/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pathname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:18:18 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/20 15:18:23 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	confirm_pathname(char **pathname, char **tmp)
{
	char	*s;

	if (access(*tmp, X_OK) == 0 && !is_dir(*tmp))
	{
		free(*pathname);
		*pathname = *tmp;
		return (1);
	}
	else if (!*pathname && access(*tmp, F_OK) == 0 && !is_dir(*tmp))
		*pathname = *tmp;
	else
	{
		if (tmp && *tmp)
		{
			s = *tmp;
			*tmp = NULL;
			free(s);
		}
	}
	return (0);
}

static int	find_pathname(char **pathname, t_list *path_list, char *cmd_name)
{
	int		cmd_name_len;
	int		pathname_len;
	int		content_len;
	char	*tmp;

	cmd_name_len = ft_strlen(cmd_name);
	tmp = NULL;
	while (path_list)
	{
		content_len = ft_strlen(path_list->content);
		pathname_len = content_len + 1 + cmd_name_len;
		tmp = malloc(sizeof(char) * (pathname_len) + 1);
		if (!tmp)
			return (0);
		memcpy(tmp, path_list->content, content_len);
		tmp[content_len] = '/';
		memcpy(tmp + content_len + 1, cmd_name, cmd_name_len);
		tmp[pathname_len] = '\0';
		if (confirm_pathname(pathname, &tmp))
			return (1);
		path_list = path_list->next;
	}
	return (1);
}

static int	append_path(t_list **path_list, char *path, char *colon)
{
	t_list	*new_node;
	char	*path_part;
	int		len;

	if (colon)
		len = colon - path;
	else
		len = ft_strlen(path);
	if (len != 0)
	{
		path_part = (char *)malloc(len + 1);
		if (path_part)
			ft_strlcpy(path_part, path, len + 1);
	}
	else
		path_part = ft_strdup(".");
	if (!path_part)
		return (0);
	new_node = ft_lstnew(path_part);
	if (!new_node)
		return (0);
	ft_lstadd_back(path_list, new_node);
	return (1);
}

static int	set_path_list(t_list **path_list)
{
	char	*colon;
	char	*path;

	*path_list = NULL;
	path = get_variable_environ(0, "PATH", 4);
	if (!path || !*path)
		return (1);
	colon = ft_strchr(path, ':');
	while (colon)
	{
		if (!append_path(path_list, path, colon))
			return (ft_lstclear(path_list, free), 0);
		path = colon + 1;
		colon = ft_strchr(path, ':');
	}
	if (!append_path(path_list, path, colon))
		return (ft_lstclear(path_list, free), 0);
	return (1);
}

int	set_pathname(char **pathname, char *cmd_name)
{
	t_list	*path_list;

	if (ft_strchr(cmd_name, '/'))
		return ((*pathname = ft_strdup(cmd_name)) != NULL);
	if (!set_path_list(&path_list))
		return (0);
	if (!path_list)
		return ((*pathname = ft_strdup(cmd_name)) != NULL);
	if (!find_pathname(pathname, path_list, cmd_name))
		return (ft_lstclear(&path_list, free), 0);
	return (ft_lstclear(&path_list, free), 1);
}
