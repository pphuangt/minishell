/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:45:09 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/25 12:45:13 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_gnl(t_gnl **src)
{
	free((*src)->str);
	free(*src);
	*src = NULL;
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	c_dst = (unsigned char *) dst;
	c_src = (const unsigned char *) src;
	if (dst > src)
	{
		while (len > 0)
		{
			c_dst[len - 1] = c_src[len - 1];
			len--;
		}
	}
	else if (dst < src)
	{
		while (len > 0)
		{
			*c_dst = *c_src;
			c_dst++;
			c_src++;
			len--;
		}
	}
	return (dst);
}
