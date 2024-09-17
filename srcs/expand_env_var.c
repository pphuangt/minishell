/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:44:25 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/17 13:44:32 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(char *str, size_t size, char **env)
{
	if (!str || size == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (strncmp(*env, str, size) == 0 && *(*env + size) == '=')
			return (*env + size + 1);
		env++;
	}
	return (NULL);
}

static void	set_quote_status(char c, char *quote_status)
{
	char	c;

	if (strchr(QUOTE, c))
	{
		if (*quote_status == 0)
			*quote_status = c;
		else if (*quote_status == c)
			*quote_status = 0;
	}
}

static int	cal_ret_size(char *str, char **env)
{
	char	*value;
	int		i;
	int		ret;
	char	quote_status;

	ret = 0;
	quote_status = 0;
	while (*str)
	{
		i = 0;
		set_quote_status(&str, &quote_status, NULL, NULL);
		if (*str == '$' && quote_status != '\'')
		{
			while (isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			value = get_env_var(str + 1, i, env);
			if (value)
				ret += strlen(value);
			str += i;
		}
		if (i == 0)
			ret++;
		str++;
	}
	return (ret);
}

char	*expand_env_var(char *str, char **env)
{
}
