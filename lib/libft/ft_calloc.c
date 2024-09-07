/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:54:09 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/11 21:37:24 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	n_size;

	if (count == 0 || size == 0)
		return (malloc(0));
	n_size = count * size;
	if (count != n_size / size || n_size > INT_MAX)
		return (NULL);
	res = malloc(n_size);
	if (!res)
		return (NULL);
	ft_bzero(res, n_size);
	return (res);
}
