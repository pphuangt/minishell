/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:06:41 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/09 22:06:48 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_mask(char *s, int i, int *mask_status)
{
	if (*mask_status == 0)
		*mask_status = s[i];
	else
		*mask_status = 0;
}

static void	skip_quote(char *s, int i, int *j, char *quote_status)
{
	if (*quote_status == s[i])
		*quote_status = 0;
	else if (*quote_status == 0)
		*quote_status = s[i];
	else
	{
		s[*j] = s[i];
		*j = *j + 1;
	}
}

char	*strip_quotes(char *s)
{
	int			i;
	int			j;
	char		quote_status;
	static int	mask_status = 0;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	quote_status = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 0x01 || s[i] == 0x02)
			skip_mask(s, i, &mask_status);
		else if (!mask_status && ft_strchr(QUOTE, s[i]))
			skip_quote(s, i, &j, &quote_status);
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
	return (s);
}
