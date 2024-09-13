/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:00:44 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/05 09:00:50 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printcmd(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;
	int			argc;
	ssize_t		size;
	char		buffer[MAXLINE + 1];

	argc = 0;
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		while (execcmd->argv[argc])
			printf("%s ", execcmd->argv[argc++]);
		printf("--> command\n");
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		printcmd(redircmd->cmd);
		if (redircmd->mode == O_RDONLY)
			printf("redir fd=%d (<) to %s --> redir\n",\
			redircmd->fd, redircmd->file.s);
		else if (redircmd->mode == O_DSYNC)
		{
			printf("heredoc fd=%d (<<) delimeter={%s} --> redir\n",\
			redircmd->fd, redircmd->file.s);
			printf("Reading from the heredoc:\n");
			size = read(redircmd->fd, buffer, MAXLINE);
			while (size > 0)
			{
				buffer[size] = '\0';
				printf("%s", buffer);
				size = read(redircmd->fd, buffer, MAXLINE);
			}
			close(redircmd->fd);
		}
		else if (redircmd->mode == (O_WRONLY | O_CREAT | O_TRUNC))
			printf("redir fd=%d (>) to %s --> redir\n",\
			redircmd->fd, redircmd->file.s);
		else if (redircmd->mode == (O_WRONLY | O_CREAT | O_APPEND))
			printf("redir fd=%d (>>) to %s --> redir\n",\
			redircmd->fd, redircmd->file.s);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		printcmd(pipecmd->left);
		printf("%s --> pipe\n", "|");
		printcmd(pipecmd->right);
	}
}

char	*get_env(char *str, char **envp)
{
	size_t	len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
