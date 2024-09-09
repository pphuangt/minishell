/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:38:17 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/06 16:38:25 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_var(char **str, char **s, int i, char **envp)
{
	char	*t;
	int		j;
	char	c;

	(*s)[i] = '\0';
	t = *s + i + 1;
	j = 0;
	c = 0;
	while (t[j] != '\0' && isvar(t[j]))
		j++;
	c = t[j];
	t[j] = '\0';
	if (join_util(str, *s) < 0)
		return (-1);
	if (join_util(str, get_env(t, envp)) < 0)
		return (-1);
	t[j] = c;
	*s = t + j;
	return (0);
}

static int	do_expand(char **str, char **envp, int *isexpand)
{
	char	*s;
	int		i;
	char	q;

	s = *str;
	i = 0;
	q = 0;
	*str = NULL;
	while (s[i])
	{
		lpeek(s, &i, &q);
		if (s[i] == '$' && s[i + 1] != '\0')
		{
			if (expand_var(str, &s, i, envp) < 0)
				return (-1);
			i = 0;
		}
		else
		{
			if (join_var(str, &s, &i) < 0)
				return (-1);
		}
		*isexpand = 1;
	}
	return (0);
}

static int	expanding_process(t_cmd *cmd, char **envp)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	int			argc;

	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		argc = 0;
		while (ecmd->argv[argc])
		{
			*ecmd->eargv[argc] = 0;
			if (do_expand(&ecmd->argv[argc], envp, &ecmd->isexpand) < 0)
				return (-1);
			remove_quote(ecmd->argv[argc++]);
		}
		remove_null(ecmd->argv);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (do_expand(&rcmd->f.file, envp, &argc) < 0)
			return (-1);
		remove_quote(rcmd->f.file);
	}
	return (0);
}

int	expandation(t_cmd *cmd, char **envp)
{
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC && expanding_process(cmd, envp) < 0)
		return (-1);
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (expandation(rcmd->cmd, envp) < 0)
			return (-1);
		*rcmd->f.efile = '\0';
		if (expanding_process(cmd, envp) < 0)
			return (-1);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (expandation(pcmd->left, envp) < 0)
			return (-1);
		if (expandation(pcmd->right, envp) < 0)
			return (-1);
	}
	return (0);
}
