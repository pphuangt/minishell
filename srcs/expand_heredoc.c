/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:50:15 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/19 11:50:22 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cal_ret_size(char *str, char **env)
{
	char	*value;
	int		i;
	int		ret;

	ret = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$')
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

static int	env_var_cpy(char *dst, char *src, int i, char **env)
{
	char	*str;
	int		ret;

	str = get_env_var(src, i, env);
	ret = 0;
	if (str)
	{
		ret = strlen(str);
		memcpy(dst, str, ret);
	}
	return (ret);
}

char	*expand_heredoc(char *str, char **env)
{
	char	*ret;
	int		size;
	int		i;

	size = cal_ret_size(str, env);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	size = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$')
		{
			while (isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			size += env_var_cpy(ret + size, str + 1, i, env);
			str += i;
		}
		if (i == 0)
			ret[size++] = *str;
		str++;
	}
	ret[size] = '\0';
	return (ret);
}
