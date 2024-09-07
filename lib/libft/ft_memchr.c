/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:28:51 by pphuangt          #+#    #+#             */
/*   Updated: 2023/08/29 14:49:18 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	c_c;
	char	*s_c;

	c_c = (char)c;
	s_c = (char *)s;
	while (n > 0)
	{
		if (*s_c == c_c)
			return (s_c);
		s_c++;
		n--;
	}
	return (NULL);
}
