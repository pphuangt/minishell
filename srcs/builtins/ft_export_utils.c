#include "minishell.h"

int	print_err_msg(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

int	cmp_strings(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	is_valid_path(char *arg)
{
	int	i;

	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while ((ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] == '=')
		return (1);
	if (!arg[i])
		return (1);
	return (0);
}

char	*get_path_name(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(str + i) && *(str + i) != '=')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i + 1);
	return (tmp);
}
