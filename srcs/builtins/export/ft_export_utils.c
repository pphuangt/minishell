/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:11:05 by paradari          #+#    #+#             */
/*   Updated: 2024/10/20 18:11:06 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	while (*(str + i) && *(str + i) != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(ret, str, i + 1);
	if (!ret)
		err_ret("malloc");
	return (ret);
}

int	is_sort(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			break ;
		else if (str1[i] == '=' && str2[i] == '=')
			break ;
		i++;
	}
	if (str1[i] < str2[i])
		return (0);
	return (1);
}

void	free_double_p(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free (str);
	str = NULL;
}
