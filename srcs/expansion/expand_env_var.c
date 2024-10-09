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

static int	env_var_cpy(char *dst, char *src, int *i, int exit_status)
{
	char	*str;
	int		ret;

	ret = 0;
	if (*i == 0 && *src == '?')
	{
		ret = get_exit_status(dst, exit_status);
		*i = *i + 1;
	}
	else
	{
		str = get_variable_environ(src, *i);
		if (str)
		{
			*dst = 0x01;
			ret = ft_strlen(str);
			ft_memcpy(dst + 1, str, ret);
			*(dst + ret + 1) = 0x02;
			ret += 2;
		}
	}
	return (ret);
}

char	*expand_env_var(char *str, int exit_status)
{
	char	*ret;
	int		size;
	int		i;

	size = cal_ret_size(str, exit_status);
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
			size += env_var_cpy(ret + size, str + 1, &i, exit_status);
		}
		if (i == 0)
			ret[size++] = *str;
		str += i + 1;
	}
	ret[size] = '\0';
	return (ret);
}
