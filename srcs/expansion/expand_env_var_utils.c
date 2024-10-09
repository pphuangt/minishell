/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:54:45 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/09 18:54:53 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cal_ret_size(char *str, int exit_status)
{
	char	*value;
	int		i;
	int		ret;

	ret = 0;
	while (*str)
	{
		i = 0;
		if (*str == '$' && *(str + 1) == '?' && ++i)
			ret += get_exit_status(NULL, exit_status);
		else if (*str == '$')
		{
			while (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				i++;
			value = get_variable_environ(str + 1, i);
			if (value)
				ret += ft_strlen(value) + 2;
		}
		if (i == 0)
			ret++;
		str += i + 1;
	}
	return (ret);
}
