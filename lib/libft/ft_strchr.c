/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:33:55 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/12 19:35:43 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_c;
	char	c_c;
	size_t	i;

	s_c = (char *)s;
	c_c = (char)c;
	i = 0;
	while (s_c[i] != '\0')
	{
		if (s_c[i] == c_c)
			return (s_c + i);
		i++;
	}
	if (s_c[i] == c_c)
		return (s_c + i);
	return (NULL);
}
