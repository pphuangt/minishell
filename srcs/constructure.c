/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:06:46 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/05 13:06:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*execcmd;

	execcmd = malloc(sizeof(*execcmd));
	if (!execcmd)
	{
		err_ret("execcmd malloc");
		return (NULL);
	}
	execcmd->type = EXEC;
	execcmd->argc = 0;
	return ((t_cmd *)execcmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*pipecmd;

	pipecmd = malloc(sizeof(*pipecmd));
	if (!pipecmd)
	{
		err_ret("pipecmd malloc");
		return (NULL);
	}
	pipecmd->type = PIPE;
	pipecmd->left = left;
	pipecmd->right = right;
	return ((t_cmd *)pipecmd);
}

t_cmd	*redircmd(t_cmd *subcmd, t_string *file, int mode, int fd)
{
	t_redircmd	*redircmd;

	redircmd = malloc(sizeof(*redircmd));
	if (!redircmd)
	{
		err_ret("redircmd malloc");
		return (NULL);
	}
	redircmd->type = REDIR;
	redircmd->cmd = subcmd;
	redircmd->file.s = file->s;
	redircmd->file.e = file->e;
	redircmd->mode = mode;
	redircmd->fd = fd;
	return ((t_cmd *)redircmd);
}
