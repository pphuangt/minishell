#include "minishell.h"

int	is_valid_varname(char *str)
{
	int	i;

	i = 0;
	if (!str || (str[i] != '_' && !ft_isalpha(str[i])))
		return (0);
	i++;
	while ((ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (!str[i] || str[i] == '=')
		return (1);
	return (0);
}
