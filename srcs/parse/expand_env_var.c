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

static int	cal_ret_size(char *str)
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
			while (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			value = get_variable_environ(str + 1, i);
			if (value)
				ret += ft_strlen(value);
			str += i;
		}
		if (i == 0)
			ret++;
		str++;
	}
	return (ret);
}

static int	env_var_cpy(char *dst, char *src, int i)
{
	char	*str;
	int		ret;

	str = get_variable_environ(src, i);
	ret = 0;
	if (str)
	{
		ret = ft_strlen(str);
		ft_memcpy(dst, str, ret);
	}
	return (ret);
}

char	*expand_env_var(char *str)
{
	char	*ret;
	int		size;
	int		i;

	size = cal_ret_size(str);
	ret = malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	size = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$')
		{
			while (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			size += env_var_cpy(ret + size, str + 1, i);
			str += i;
		}
		if (i == 0)
			ret[size++] = *str;
		str++;
	}
	ret[size] = '\0';
	return (ret);
}
