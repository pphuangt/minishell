/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:33:45 by pphuangt          #+#    #+#             */
/*   Updated: 2024/09/06 16:33:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(char *s)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	q = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(QUOTE, s[i]))
		{
			if (q == s[i])
				q = 0;
			else if (q == 0)
				q = s[i];
			else
				s[j++] = s[i];
		}
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

void	remove_null(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0')
		{
			argv[j] = argv[i];
			j++;
		}
		i++;
	}
	if (j != 0)
		argv[j] = 0;
}

int	join_help(char **token, char *s)
{
	char	*sj;

	sj = ft_strjoin(*token, s);
	if (!sj)
		return (-1);
	free(*token);
	*token = sj;
	return (0);
}

int	join_var(char **token, char **s, int *i)
{
	char	*sj;

	sj = ft_strjoin(*token, *s);
	if (!sj)
		return (-1);
	free(*token);
	*token = sj;
	if ((*s)[*i] != '\0')
	{
		*s = *s + ft_strlen(*s);
		*i = 0;
	}
	return (0);
}

void	lpeek(char *s, int *i, char *q)
{
	while (s[*i] != '\0'
		&& (s[*i] != '$' || *q == '\'' || (*q && ft_strchr(DELI, s[*i + 1]))))
	{
		if (ft_strchr(QUOTE, s[*i]))
		{
			if (*q == 0)
				*q = s[*i];
			else if (*q == s[*i])
				*q = 0;
		}
		*i = *i + 1;
	}
}
