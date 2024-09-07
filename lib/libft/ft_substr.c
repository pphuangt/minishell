/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:45:34 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/01 12:49:56 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	size;
	char	*res;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	size = s_len - start;
	if (start > s_len)
		size = 0;
	else if (size >= len)
		size = len;
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (size == 0)
		*res = '\0';
	else
		ft_strlcpy(res, s + start, size + 1);
	return (res);
}
