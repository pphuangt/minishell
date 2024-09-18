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

t_cmd	*err_parse_exec(t_cmd *cmd, char *msg, char *tok)
{
	char	*str;
	char	*t;

	if (msg)
		err_msg(0, msg);
	else if (tok)
	{
		if (!*tok)
			err_msg(0, "systax error near unexpected token `newline'");
		else
		{
			str = ft_strdup("systax error near unexpected token `_'");
			if (str)
			{
				t = ft_strchr(str, '_');
				*t = *tok;
				err_msg(0, str);
			}
			else
				err_ret("error message");
		}
	}
	free_parse_exec(cmd);
	return (NULL);
}

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
