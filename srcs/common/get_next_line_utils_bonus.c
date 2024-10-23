/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:18 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/28 10:58:32 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gnl	*find_node(t_gnl *head, int fd)
{
	t_gnl	*cur;

	cur = head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	free_t_gnl(t_gnl **head, int fd)
{
	t_gnl	*tmp;
	t_gnl	*prev;

	tmp = *head;
	prev = NULL;
	if (tmp->fd == fd)
	{
		*head = tmp->next;
		free(tmp->str);
		free(tmp);
	}
	else
	{
		while (tmp != NULL && tmp->fd != fd)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = tmp->next;
		free(tmp->str);
		free(tmp);
	}
}
