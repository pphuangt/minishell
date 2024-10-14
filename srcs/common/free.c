/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:36:54 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/13 15:37:02 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	freeexec(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	int			i;

	execcmd = (t_execcmd *)cmd;
	i = 0;
	while (i < execcmd->argc)
		free(execcmd->argv[i++]);
	free(execcmd);
}

static void	freeredir(t_cmd *cmd)
{
	t_redircmd	*redircmd;

	redircmd = (t_redircmd *)cmd;
	freecmd(redircmd->cmd);
	if (redircmd->file.s == redircmd->file.e)
		free(redircmd->file.s);
	free(redircmd);
}

static void	freepipe(t_cmd *cmd)
{
	t_pipecmd	*pipecmd;

	pipecmd = (t_pipecmd *)cmd;
	freecmd(pipecmd->left);
	freecmd(pipecmd->right);
	free(pipecmd);
}

void	freecmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		freeexec(cmd);
	else if (cmd->type == REDIR)
		freeredir(cmd);
	else if (cmd->type == PIPE)
		freepipe(cmd);
}

void	free_environ(t_environ *environ)
{
	char	**envp;

	envp = environ->p;
	while (*envp)
		free(*envp++);
	free(environ->p);
	environ->p = NULL;
}
