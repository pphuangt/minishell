/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:50:49 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/07 15:50:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_shell *shell)
{
	if (!shell->cmd)
		return ;
	if (expansion(shell) != SUCCESS)
		return ;
	printcmd(shell->cmd);
}
