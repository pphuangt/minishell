/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:42:02 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/04 13:42:09 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_exec_argv(char **ps, char *es, t_execcmd *ecmd, int *argc)
{
	t_string	string;

	if (*ps < es && !peek(ps, es, "|"))
	{
		if (gettoken(ps, es, &string.s, &string.e) < 0)
		{
			err_msg(0, "no closing quote");
			return (-1);
		}
		ecmd->argv[*argc] = string.s;
		ecmd->eargv[*argc] = string.e;
		*argc = *argc + 1;
		if (*argc == MAXARGS + 1)
		{
			err_msg(0, "to many args");
			return (-1);
		}
	}
	return (0);
}

static t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	t_cmd		*ncmd;
	int			tok;
	int			fd;
	int			mode;
	t_string	file;

	while (valid_redir(ps, es, &fd))
	{
		tok = gettoken(ps, es, 0, 0);
		mode = gettoken(ps, es, &file.s, &file.e);
		if (mode == -1)
			return (err_parse_exec(cmd, "no closing quote", NULL));
		else if (mode != 'a')
			return (err_parse_exec(cmd, NULL, file.s));
		set_fd_mode(tok, &fd, &mode);
		ncmd = redircmd(cmd, &file, mode, fd);
		if (!ncmd)
			return (err_parse_exec(cmd, NULL, NULL));
		cmd = ncmd;
		while (*ps < es && ft_strchr(WHITESPACE, **ps))
			(*ps)++;
	}
	return (cmd);
}

static t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*ret;
	t_cmd		*cmd;
	t_execcmd	*ecmd;
	int			argc;

	ret = execcmd();
	if (!ret)
		return (NULL);
	ecmd = (t_execcmd *)ret;
	argc = 0;
	while (*ps < es && !peek(ps, es, "|"))
	{
		cmd = parseredirs(ret, ps, es);
		if (!cmd)
			return (NULL);
		ret = cmd;
		if (set_exec_argv(ps, es, ecmd, &argc) < 0)
			return (err_parse_exec(ret, NULL, NULL));
	}
	ecmd->argv[argc] = 0;
	ecmd->eargv[argc] = 0;
	if (peek(ps, es, "|") && *ps == es)
		return (err_parse_exec(ret, NULL, "|"));
	return (reverse_redircmd(ret));
}

static t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_cmd	*pcmd;

	cmd = parseexec(ps, es);
	if (!cmd)
		return (NULL);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		pcmd = parsepipe(ps, es);
		if (!pcmd)
		{
			freecmd(cmd);
			return (NULL);
		}
		cmd = pipecmd(cmd, pcmd);
		if (!cmd)
		{
			freecmd(cmd);
			freecmd(pcmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_shell	*parsecmd(t_shell *shell, char	*s)
{
	char	*es;

	es = s + ft_strlen(s);
	peek(&s, es, "");
	if (s != es)
	{
		shell->cmd = parsepipe(&s, es);
		if (!shell->cmd)
			shell->exit_status = SYNTAX_ERROR;
	}
	else
		shell->exit_status = SUCCESS;
	return (shell);
}
