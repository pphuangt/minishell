/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:59:03 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/12 16:59:10 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char *qs, char c)
{
	if (*qs == c)
		*qs = 0;
	else if (*qs == 0)
		*qs = c;
}

int	is_invalid_filename(char *str)
{
	char	qs;
	int		mask;

	qs = 0;
	mask = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			handle_quote(&qs, *str);
		else if (*str == 0x01 || *str == 0x02)
		{
			if (mask == 0)
				mask = *str;
			else if (mask == *str)
				mask = 0;
		}
		else if (mask && !qs && ft_strchr(WHITESPACE, *str))
			return (1);
		str++;
	}
	return (0);
}
