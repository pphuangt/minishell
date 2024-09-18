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

int	getstr(char **s, char *es, int *ret)
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
	*ret = 'a';
	return (0);
}

int	get_meta(char **s, int *ret)
{
	char	*ss;

	ss = *s;
	if (ft_strchr(REDIR_O, **s))
	{
		(*s)++;
		if (**s == '<' && *ss == '<')
		{
			*ret = '-';
			(*s)++;
		}
		else if (**s == '>' && *ss == '>')
		{
			*ret = '+';
			(*s)++;
		}
	}
	else if (ft_strchr(METACHARACTER, **s))
		(*s)++;
	return (*s - ss);
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	int		ret;
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	ret = *s;
	if (q)
		*q = s;
	if (!*s)
		return (0);
	if (!get_meta(&s, &ret) && getstr(&s, es, &ret) < 0)
		return (-1);
	if (eq)
		*eq = s;
	*ps = s;
	return (ret);
}
