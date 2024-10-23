/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:45:53 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/25 12:45:58 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
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
	char		*str;
	ssize_t		length;
	ssize_t		size;
}	t_gnl;

char	*get_next_line(int fd);
void	free_gnl(t_gnl **src);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
