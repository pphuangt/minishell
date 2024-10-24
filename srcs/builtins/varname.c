/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varname.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:53:12 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/24 19:53:14 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_varname(char *str)
{
	int	i;

	i = 0;
	if (!str || (str[i] != '_' && !ft_isalpha(str[i])))
		return (0);
	i++;
	while ((ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (!str[i] || str[i] == '=')
		return (1);
	return (0);
}
