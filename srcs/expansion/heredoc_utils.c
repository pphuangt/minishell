/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:17:11 by pphuangt          #+#    #+#             */
/*   Updated: 2024/10/23 15:17:13 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_hd_file(t_redircmd *rcmd)
{
	char	*filename;
	int		fd;

	filename = generate_file();
	if (!filename)
		return (-1);
	fd = open(filename,
			O_CREAT | O_RDWR | O_TRUNC,
			(S_IRUSR + S_IWUSR) | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (free(filename), err_ret("open"), -1);
	rcmd->hd = filename;
	return (fd);
}
