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

static void	lpeek(char *s, int *i, char *q)
{
	while (s[*i] != '\0'
		&& (s[*i] != '$' || *q == '\'' || (*q && !isvar(s[*i + 1]))))
	{
		if (ft_strchr(QUOTE, s[*i]))
		{
			if (*q == 0)
				*q = s[*i];
			else if (*q == s[*i])
				*q = 0;
		}
		*i = *i + 1;
	}
}

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

static int	do_expand(char **str, char **envp)
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
	}
	return (0);
}

static int	expanding_process(t_cmd *cmd, char **envp)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[ecmd->argc])
		{
			*ecmd->eargv[ecmd->argc] = 0;
			if (do_expand(&ecmd->argv[ecmd->argc], envp) < 0)
				return (-1);
			remove_quote(ecmd->argv[ecmd->argc++]);
		}
		remove_null(ecmd->argv);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (do_expand(&rcmd->file.s, envp) < 0)
			return (-1);
		remove_quote(rcmd->file.s);
		if (rcmd->mode == O_DSYNC && heredoc_process(cmd) == -1)
			return (-1);
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
		*rcmd->file.e = '\0';
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
