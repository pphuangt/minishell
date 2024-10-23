/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:46:25 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/28 10:46:26 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# define DS 100
# define DB 2

# define BS BUFFER_SIZE

typedef struct s_gnl
{
	int				fd;
	char			*str;
	ssize_t			length;
	ssize_t			size;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
void	free_t_gnl(t_gnl **head, int fd);
void	*ft_memmove(void *dst, const void *src, size_t len);
t_gnl	*find_node(t_gnl *head, int fd);

#endif
