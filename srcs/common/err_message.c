/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:22:34 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/10 19:22:48 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_tok(char *stok, char *etok)
{
	ft_putstr_fd("minishell: systax error near unexpected token `"\
	, STDERR_FILENO);
	if (!*stok)
		ft_putendl_fd("newline'", STDERR_FILENO);
	else
	{
		if (etok)
			*etok = 0;
		ft_putstr_fd(stok, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
}

void	err_filename(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}
