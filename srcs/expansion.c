/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:17:14 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/16 11:17:21 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_matching_quotes(char *s)
{
	int		i;
	int		j;
	char	quote_status;

	i = 0;
	j = 0;
	quote_status = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(QUOTE, s[i]))
		{
			if (quote_status == s[i])
				quote_status = 0;
			else if (quote_status == 0)
				quote_status = s[i];
			else
				s[j++] = s[i];
		}
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
	return (s);
}

static int	expand_filename(char **filename)
{
	char	*str;
	char	*msg;

	str = expand_env_var(*filename);
	if (!str)
	{
		err_ret("malloc expand environment variable");
		return (-1);
	}
	if (!*str)
	{
		msg = ft_strjoin(*filename, ": ambiguous redirect");
		if (msg)
			err_ret(msg);
		free(str);
		return (-1);
	}
	*filename = strip_matching_quotes(str);
	return (0);
}

static int	expand_exec(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	char		*str;
	int			argc;

	ecmd = (t_execcmd *)cmd;
	argc = 0;
	while (ecmd->argv[argc])
	{
		*ecmd->eargv[argc] = 0;
		str = expand_env_var(ecmd->argv[argc]);
		if (!str)
		{
			err_ret("expand environment variable");
			return (-1);
		}
		if (*str)
			ecmd->argv[ecmd->argc++] = strip_matching_quotes(str);
		else
			free(str);
		argc++;
	}
	ecmd->argv[ecmd->argc] = 0;
	return (0);
}

static int	expand_redir(t_shell *shell, t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (expansion(shell, rcmd->cmd) < 0)
		return (-1);
	*rcmd->file.e = '\0';
	if (rcmd->mode == O_DSYNC)
	{
		if (heredoc(shell, rcmd) < 0)
			return (-1);
	}
	else
	{
		if (expand_filename(&rcmd->file.s) < 0)
			return (-1);
		rcmd->file.e = rcmd->file.s;
	}
	return (0);
}

int	expansion(t_shell *shell, t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	if (!cmd)
		return (0);
	if (cmd->type == EXEC)
	{
		if (expand_exec(cmd) < 0)
			return (-1);
	}
	else if (cmd->type == REDIR)
	{
		if (expand_redir(shell, cmd) < 0)
			return (-1);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		if (expansion(shell, pcmd->left) < 0)
			return (-1);
		if (expansion(shell, pcmd->right) < 0)
			return (-1);
	}
	return (0);
}
