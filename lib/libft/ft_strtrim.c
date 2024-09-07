/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:30:06 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/12 19:22:04 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char		*res;
	size_t		l;
	size_t		r;
	size_t		size;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	l = 0;
	r = ft_strlen(s1);
	if (r != 0)
	{
		while (ft_strchr(set, s1[l]) && s1[l] != '\0')
			l++;
		while (ft_strchr(set, s1[r - 1]) && r > l && s1[r - 1] != '\0')
			r--;
	}
	size = r - l;
	res = malloc(size + 1);
	if (res)
		ft_strlcpy(res, s1 + l, size + 1);
	return (res);
}
