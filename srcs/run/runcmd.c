/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:02:29 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/30 15:02:35 by pphuangt         ###   ########.fr       */
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

	path = ft_split(get_variable_environ("PATH", 4), ':');
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

void	runcmd_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	char		*pathname;
	extern char	**environ;

	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == 0)
		exit(0);
	pathname = ecmd->argv[0];
	if (!ft_strchr(ecmd->argv[0], '/'))
		pathname = search_pathname(ecmd->argv[0], ft_strlen(ecmd->argv[0]));
	if (!pathname)
	{
		ft_putstr_fd(ecmd->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(0);
	}
	execve(pathname, ecmd->argv, environ);
	err_ret(pathname);
}

void	runcmd_recursive(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		runcmd_exec(cmd);
}

void	runcmd(t_cmd *cmd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		err_ret("fork");
		return ;
	}
	if (pid == 0)
	{
		runcmd_recursive(cmd);
		exit(0);
	}
	else
		wait(&wstatus);
}
