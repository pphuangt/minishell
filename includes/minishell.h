/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:40:57 by pphuangt          #+#    #+#             */
/*   Updated: 2024/06/24 15:40:59 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "define.h"

void	init_shell(t_shell *shell);
int		init_signal(t_shell *shell);
int		init_environ(t_environ *environ);
char	*rl_gets(t_shell *shell, char *prompt, bool add_in_history);

#endif
