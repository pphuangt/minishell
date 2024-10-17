/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:10:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/10 12:10:48 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd_mode(int tok, int *fd, int *mode)
{
	if (*fd == -1)
	{
		if (tok == '<' || tok == '-')
			*fd = 0;
		else if (tok == '>' || tok == '+')
			*fd = 1;
	}
	if (tok == '<')
		*mode = O_RDONLY;
	else if (tok == '>')
		*mode = O_CREAT | O_RDWR | O_TRUNC;
	else if (tok == '+')
		*mode = O_CREAT | O_RDWR | O_APPEND;
	else if (tok == '-')
		*mode = O_DSYNC;
}

int	valid_redir(char **ps, char *es, int *fd)
{
	char	*s;

	s = *ps;
	*fd = -1;
	while (s < es && ft_isdigit(*s))
		s++;
	if (s < es && ft_strchr(REDIR_O, *s))
	{
		if (s != *ps)
		{
			*fd = ft_atoi(*ps);
			*ps = s;
		}
		return (1);
	}
	return (0);
}

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
