/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paradari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:10:55 by paradari          #+#    #+#             */
/*   Updated: 2024/10/20 18:10:56 by paradari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_sort(char *str1, char *str2);
char	*extract_key(char *str);
void	free_double_p(char **str);

void	ft_swap(char **str, int j)
{
	char	*tmp;

	tmp = str[j];
	str[j] = str[j + 1];
	str[j + 1] = tmp;
}

char	**get_sort_env(t_environ *environ)
{
	char	**sorted;
	size_t	i;
	size_t	j;

	sorted = malloc(sizeof(char *) * (environ->len + 1));
	if (!sorted)
		return (NULL);
	i = -1;
	while (++i < environ->len)
		sorted[i] = ft_strdup(environ->p[i]);
	sorted[i] = NULL;
	i = -1;
	while (++i < environ->len)
	{
		j = 0;
		while (j < environ->len - i - 1 && sorted[j + 1])
		{
			if (is_sort(sorted[j], sorted[j + 1]))
				ft_swap(sorted, j);
			j++;
		}
	}
	return (sorted);
}

void	print_sort(char *name, int max_len, int cur_len, char **sorted)
{
	char	*str;

	ft_putstr_fd(name, STDOUT_FILENO);
	str = sorted[max_len - cur_len] + ft_strlen(name) + 1;
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
}

int	print_exported_env(t_environ *environ)
{
	char	**sorted;
	char	*name;
	int		len;
	int		nlen;

	len = environ->len;
	sorted = get_sort_env(environ);
	while (len > 0)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		name = extract_key(sorted[environ->len - len]);
		nlen = ft_strlen(name);
		if (sorted[environ->len - len][nlen])
			print_sort(name, environ->len, len, sorted);
		else
			ft_putendl_fd(name, STDOUT_FILENO);
		free(name);
		len--;
	}
	free_double_p(sorted);
	return (SUCCESS);
}

void	print_err_msg(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
