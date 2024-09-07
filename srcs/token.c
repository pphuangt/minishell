/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:20:04 by pphuangt          #+#    #+#             */
/*   Updated: 2024/07/05 11:20:11 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	peekcmd(char **s, char *es)
{
	char	*q;

	q = 0;
	while (*s < es && (q || !ft_strchr(METACHARACTER, **s)))
	{
		if (q && *q == **s)
			q = 0;
		else if (!q && ft_strchr(QUOTE, **s))
			q = *s;
		(*s)++;
	}
	if (q != 0)
		return (-1);
	return (0);
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	int		ret;
	char	*s;

	s = *ps;
	if (!(*s))
		return (0);
	ret = *s;
	if (q)
		*q = s;
	if (ft_strchr(METACHARACTER, *s))
		s++;
	else if (peekcmd(&s, es) < 0)
		return (-1);
	if (eq)
		*eq = s;
	*ps = s;
	return (ret);
}
