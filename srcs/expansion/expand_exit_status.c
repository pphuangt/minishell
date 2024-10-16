/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:11:29 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/09 18:11:34 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(char *dst, int exit_status)
{
	int	ret;
	int	tmp;

	ret = 0;
	tmp = exit_status;
	if (tmp == 0)
		ret = 1;
	while (tmp != 0)
	{
		ret++;
		tmp /= 10;
	}
	if (!dst)
		return (ret);
	tmp = ret;
	while (tmp > 0)
	{
		dst[--tmp] = '0' + (exit_status % 10);
		exit_status /= 10;
	}
	return (ret);
}
