/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:26:39 by pphuangt          #+#    #+#             */
/*   Updated: 2023/08/29 13:49:51 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_c;
	char	c_c;
	size_t	i;

	s_c = (char *)s;
	c_c = (char)c;
	i = ft_strlen(s);
	if (c_c == '\0')
		return (s_c + i);
	while (i > 0)
	{
		if (s_c[i - 1] == c_c)
			return (s_c + i - 1);
		i--;
	}
	return (NULL);
}
