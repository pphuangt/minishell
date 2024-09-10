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

t_cmd	*err_parse_exec(t_execcmd *exec_cmd, char *msg)
{
	err_msg(0, msg);
	free(exec_cmd);
	return (NULL);
}

void	set_fd(int tok, int *fd, t_string *string)
{
	char	*s;
	char	c;

	if (string)
		s = string->s;
	if (*fd)
	{
		while (s < string->e && ft_isdigit(*s))
			s++;
		*fd = -1;
		if (s == string->e)
		{
			c = *(string->e);
			*string->e = '\0';
			*fd = ft_atoi(string->s);
			*string->e = c;
			string->s = NULL;
		}
	}
	if (!string || *fd == -1)
	{
		if (tok == '<' || tok == '-')
			*fd = 0;
		else if (tok == '>' || tok == '+')
			*fd = 1;
	}
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
