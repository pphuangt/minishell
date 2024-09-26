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

t_cmd	*reverse_redircmd(t_cmd *cmd)
{
	t_cmd		*prev;
	t_cmd		*curr;
	t_cmd		*next;
	t_redircmd	*rcmd;

	if (cmd->type == EXEC)
		return (cmd);
	prev = NULL;
	curr = cmd;
	rcmd = NULL;
	while (curr->type == REDIR)
	{
		rcmd = (t_redircmd *)curr;
		next = rcmd->cmd;
		rcmd->cmd = prev;
		prev = curr;
		curr = next;
	}
	rcmd = (t_redircmd *)cmd;
	rcmd->cmd = curr;
	return (prev);
}

void	printcmd(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;
	int			argc;
	ssize_t		size;
	char		buffer[MAXLINE + 1];

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		argc = 0;
		execcmd = (t_execcmd *)cmd;
		while (execcmd->argv[argc])
			printf("{%s} ", execcmd->argv[argc++]);
		printf("--> command\n");
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
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
		printcmd(redircmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		printcmd(pipecmd->left);
		printf("%s --> pipe\n", "|");
		printcmd(pipecmd->right);
	}
}
