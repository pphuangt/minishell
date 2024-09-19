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

char	*get_env_var(char *str, size_t size, char **env)
{
	if (!str || size == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, str, size) == 0 && *(*env + size) == '=')
			return (*env + size + 1);
		env++;
	}
	return (NULL);
}

static int	update_qs(char *qs, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (*qs == 0)
			*qs = c;
		else if (*qs == c)
			*qs = 0;
		return (1);
	}
	return (0);
}

static int	cal_ret_size(char *str, char **env)
{
	char	*value;
	int		i;
	int		ret;
	char	qs;

	ret = 0;
	qs = 0;
	while (*str)
	{
		i = 0;
		if (!update_qs(&qs, *str) && *str == '$' && qs != '\'')
		{
			while (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			value = get_env_var(str + 1, i, env);
			if (value)
				ret += ft_strlen(value);
			str += i;
		}
		if (i == 0 && qs != *str && (qs != 0 || !ft_strchr(QUOTE, *str)))
			ret++;
		str++;
	}
	return (ret);
}

static int	env_var_cpy(char *dst, char *src, int *i, char **env)
{
	char	*str;
	int		ret;

	while (ft_isalnum(src[*i + 1]) || src[*i + 1] == '_')
		*i = *i + 1;
	str = get_env_var(src + 1, *i, env);
	ret = 0;
	if (str)
	{
		while (*str)
		{
			*dst = *str;
			str++;
			dst++;
			ret++;
		}
	}
	return (ret);
}

char	*expand_env_var(char *str, char **env)
{
	char	*ret;
	int		size;
	int		i;
	char	qs;

	size = cal_ret_size(str, env);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	size = 0;
	qs = 0;
	while (*str)
	{
		i = 0;
		if (!update_qs(&qs, *str) && *str == '$' && qs != '\'')
		{
			size += env_var_cpy(ret + size, str, &i, env);
			str += i;
		}
		if (i == 0 && qs != *str && (qs != 0 || !ft_strchr(QUOTE, *str)))
			ret[size++] = *str;
		str++;
	}
	ret[size] = '\0';
	return (ret);
}
