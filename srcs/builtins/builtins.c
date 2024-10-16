#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	freecmd(shell->cmd);
	shell->cmd = NULL;
	free(shell->input);
	shell->input = NULL;
	free_environ(&shell->environ);
	printf("exit\n");
	exit(shell->exit_status);
}
