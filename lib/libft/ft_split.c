/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:42:08 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/08 18:58:27 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_size(const char *s, char c)
{
	size_t	res;
	size_t	i;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			res++;
		i++;
	}
	return (res);
}

static void	free_split(char **res)
{
	char	**cur;

	cur = res;
	while (*cur)
	{
		free(*cur);
		cur++;
	}
	free(res);
}

static int	write_split(char **res, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		j = 0;
		if (s[i] != c)
		{
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			res[word] = (char *)malloc(sizeof(char ) * (j + 1));
			if (!res[word])
				return (0);
			ft_strlcpy(res[word], s + i, j + 1);
			word++;
			i = i + j;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	int		is_free;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = split_size(s, c);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	is_free = write_split(res, s, c);
	if (!is_free)
	{
		free_split(res);
		return (NULL);
	}
	res[size] = NULL;
	return (res);
}
