#include "minishell.h"

int	print_exported_env(t_environ *environ)
{
	(void)environ;
	printf("print exported");
	return (SUCCESS);
}

void	print_err_msg(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
