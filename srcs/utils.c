/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:00:44 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/05 09:00:50 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*    free EXEC argv    */
void	freeargv(t_execcmd *ecmd)
{
	int	argc;
	int	i;

	argc = ecmd->argc;
	i = 0;
	while (i < argc && ecmd->argv[i])
	{
		free(ecmd->argv[i]);
		i++;
	}
}

void	freecmd(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		if (execcmd->isexpand > 0)
			freeargv(execcmd);
		free(execcmd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		freecmd(pipecmd->left);
		freecmd(pipecmd->right);
		free(pipecmd);
	}
}

void	printcmd(t_cmd *cmd)
{
	t_execcmd	*execcmd;
	t_pipecmd	*pipecmd;
	t_redircmd	*redircmd;
	int			argc;

	argc = 0;
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		execcmd = (t_execcmd *)cmd;
		while (execcmd->argv[argc])
			printf("%s ", execcmd->argv[argc++]);
		printf("--> command\n");
	}
	else if (cmd->type == REDIR)
	{
		redircmd = (t_redircmd *)cmd;
		printf("file: %s	efile: %s	fd: %d", redircmd->f.file, redircmd->f.efile, redircmd->fd);
		printf("--> redirect\n");
		printcmd(redircmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd = (t_pipecmd *)cmd;
		printcmd(pipecmd->left);
		printf("%s --> pipe\n", "|");
		printcmd(pipecmd->right);
	}
}

char	*get_env(char *str, char **envp)
{
	size_t	len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	isvar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
