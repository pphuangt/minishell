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

static void	free_parse_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		free(ecmd);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		free_parse_exec(rcmd->cmd);
		free(rcmd);
	}
}

t_cmd	*err_parse_exec(t_cmd *cmd, char *msg)
{
	if (msg)
		err_msg(0, msg);
	free_parse_exec(cmd);
	return (NULL);
}

void	set_default_fd(int tok, int *fd)
{
	if (tok == '<' || tok == '-')
		*fd = 0;
	else if (tok == '>' || tok == '+')
		*fd = 1;
}

void	set_mode(int tok, int *mode)
{
	if (tok == '<')
		*mode = O_RDONLY;
	else if (tok == '>')
		*mode = O_WRONLY | O_CREAT | O_TRUNC;
	else if (tok == '+')
		*mode = O_WRONLY | O_CREAT | O_APPEND;
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
	if (s < es && s != *ps && ft_strchr(REDIR_O, *s))
	{
		*fd = ft_atoi(*ps);
		*ps = s;
		return (1);
	}
	else if (s < es && ft_strchr(REDIR_O, *s))
	{
		*ps = s;
		return (1);
	}
	return (0);
}
