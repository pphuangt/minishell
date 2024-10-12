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

static int	variable_size(char *str, int *i, int exit_status)
{
	char	*value;
	int		ret;

	ret = 0;
	if (*(str + 1) == '?')
	{
		ret = get_exit_status(NULL, exit_status);
		*i = *i + 1;
	}
	else
	{
		while (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
			*i = *i + 1;
		value = get_variable_environ(0, str + 1, *i);
		if (value)
			ret = ft_strlen(value) + 2;
	}
	return (ret);
}

static void	handle_quote(char *qs, char c)
{
	if (*qs == c)
		*qs = 0;
	else if (*qs == 0)
		*qs = c;
}

int	cal_ret_size(char *str, int exit_status, int heredoc)
{
	int		i;
	int		ret;
	char	qs;

	ret = 0;
	qs = 0;
	while (*str)
	{
		i = 0;
		if (*str == '\'' || *str == '"')
			handle_quote(&qs, *str);
		else if (*str == '$' && (heredoc || qs != '\''))
			ret += variable_size(str, &i, exit_status);
		if (i == 0)
			ret++;
		str += i + 1;
	}
	return (ret);
}
