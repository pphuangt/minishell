/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:55:03 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/08 19:21:12 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*cur;
	t_list	*tmp;

	if (!(*f) || !(*del))
		return (NULL);
	head = NULL;
	while (lst)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		if (!tmp)
		{
			ft_lstclear(&head, del);
			return (head);
		}
		tmp->content = (*f)(lst->content);
		tmp->next = NULL;
		if (!head)
			head = tmp;
		else
			cur->next = tmp;
		cur = tmp;
		lst = lst->next;
	}
	return (head);
}
