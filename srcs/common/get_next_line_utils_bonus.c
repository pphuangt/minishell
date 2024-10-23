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

#include "get_next_line_bonus.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	c_dst = (unsigned char *) dst;
	c_src = (const unsigned char *) src;
	if (dst > src)
	{
		while (len > 0)
		{
			c_dst[len - 1] = c_src[len - 1];
			len--;
		}
	}
	else if (dst < src)
	{
		while (len > 0)
		{
			*c_dst = *c_src;
			c_dst++;
			c_src++;
			len--;
		}
	}
	return (dst);
}

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
