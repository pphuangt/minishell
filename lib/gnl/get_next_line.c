/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:43:38 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/25 12:44:04 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_gnl(t_gnl **src);

static t_gnl	*create_buff(void)
{
	t_gnl	*buff;

	buff = (t_gnl *)malloc(sizeof(t_gnl));
	if (!buff)
		return (NULL);
	buff->size = (BS < DS) * DS + (BS >= DS) * BS;
	buff->str = malloc(sizeof(char) * buff->size);
	if (!buff->str)
	{
		free(buff);
		return (NULL);
	}
	buff->length = 0;
	return (buff);
}

static int	expand_buff(t_gnl **buff)
{
	char	*n_str;

	n_str = malloc(sizeof(char) * ((*buff)->size * DB));
	if (!n_str)
	{
		free_gnl(buff);
		return (0);
	}
	ft_memmove(n_str, (*buff)->str, (*buff)->length);
	free((*buff)->str);
	(*buff)->str = n_str;
	(*buff)->size = (*buff)->size * DB;
	return (1);
}

static char	*gen_line(t_gnl **buff, ssize_t i)
{
	char	*result;

	result = malloc(sizeof(char) * (i + 1));
	if (!result)
	{
		free_gnl(buff);
		return (NULL);
	}
	result[i] = '\0';
	ft_memmove(result, (*buff)->str, i);
	ft_memmove((*buff)->str, (*buff)->str + i, (*buff)->length - i);
	(*buff)->length = (*buff)->length - i;
	if ((*buff)->length == 0)
		free_gnl(buff);
	return (result);
}

static char	*find_line(t_gnl **buff, int fd)
{
	ssize_t	size;
	ssize_t	i;

	i = 1;
	while ((*buff)->str[i - 1] != '\n')
	{
		if (i == (*buff)->length)
		{
			if ((*buff)->size - (*buff)->length < BS && !expand_buff(buff))
				return (NULL);
			size = read(fd, (*buff)->str + (*buff)->length, BUFFER_SIZE);
			(*buff)->length = (*buff)->length + size;
			if (size < 0)
			{
				free_gnl(buff);
				return (NULL);
			}
			else if (size == 0)
				break ;
		}
		i++;
	}
	return (gen_line(buff, i));
}

char	*get_next_line(int fd)
{
	static t_gnl	*buff = NULL;
	t_gnl			*tmp;
	ssize_t			size;

	tmp = buff;
	if (!buff)
	{
		buff = create_buff();
		if (!buff)
			return (NULL);
		size = read(fd, buff->str + buff->length, BUFFER_SIZE);
		if ((size == 0 && !tmp) || size < 0)
		{
			free_gnl(&buff);
			return (NULL);
		}
		buff->length = buff->length + size;
	}
	return (find_line(&buff, fd));
}
