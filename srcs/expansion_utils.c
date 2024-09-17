/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:17:51 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/16 11:17:57 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_matching_quotes(char *s)
{
	int		i;
	int		j;
	char	quote_status;

	i = 0;
	j = 0;
	quote_status = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(QUOTE, s[i]))
		{
			if (quote_status == s[i])
				quote_status = 0;
			else if (quote_status == 0)
				quote_status = s[i];
			else
				s[j++] = s[i];
		}
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

void	remove_null_entries(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			argv[j++] = argv[i];
		i++;
	}
	if (j != 0)
		argv[j] = 0;
}
