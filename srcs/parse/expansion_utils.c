/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:25:11 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/08 21:25:17 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clone_argument(char **dst, char **src)
{
	while (*src)
		*dst++ = *src++;
	*dst = 0;
}

static void	skip_double_quote(char *str, int *i)
{
	*i = *i + 1;
	while (str[*i] != '"')
		*i = *i + 1;
}

static void	skip_single_quote(char *str, int *i)
{
	*i = *i + 1;
	while (str[*i] != '\'')
		*i = *i + 1;
}

static int	handler_set_argument(t_execcmd *ecmd, char *str, int *i, int *start)
{
	char	*substr;

	*i = *i + 1;
	while (str[*i] != 0x02)
	{
		if (ft_strchr(WHITESPACE, str[*i]))
		{
			substr = ft_substr(str, *start, *i - *start);
			if (!substr)
				return (SYSTEM_ERROR);
			ecmd->argv[ecmd->argc++] = substr;
			*start = *i + 1;
		}
		*i = *i + 1;
	}
	return (SUCCESS);
}

int	set_argument(t_execcmd *ecmd, char *str)
{
	int	i;
	int	start;

	if (!*str)
		return (free(str), SUCCESS);
	i = -1;
	start = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			skip_double_quote(str, &i);
		else if (str[i] == '\"')
			skip_single_quote(str, &i);
		else if (str[i] == 0x01)
		{
			if (handler_set_argument(ecmd, str, &i, &start) == SYSTEM_ERROR)
				return (SYSTEM_ERROR);
		}
	}
	ecmd->argv[ecmd->argc++] = ft_substr(str, start, i - start);
	if (!ecmd->argv[ecmd->argc - 1])
		return (SYSTEM_ERROR);
	return (SUCCESS);
}
