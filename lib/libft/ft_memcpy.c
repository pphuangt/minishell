/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:02:03 by pphuangt          #+#    #+#             */
/*   Updated: 2023/08/28 16:51:31 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	c_dst = (unsigned char *) dst;
	c_src = (const unsigned char *) src;
	if (dst == src)
		return (dst);
	while (n > 0)
	{
		*c_dst = *c_src;
		c_dst++;
		c_src++;
		n--;
	}
	return (dst);
}
