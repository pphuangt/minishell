/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:34:41 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/05 19:39:06 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*res;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	res = malloc(sizeof(char) * (s_len + 1));
	if (!res)
		return (NULL);
	res[s_len] = '\0';
	while (s_len > 0)
	{
		res[s_len - 1] = f(s_len - 1, s[s_len - 1]);
		s_len--;
	}
	return (res);
}
