#include "minishell.h"

int	ft_echo(char **argv, int argc)
{
	(void)argv;
	(void)argc;
	printf("run echo\n");
	return (0);
}

int	ft_cd(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run cd\n");
	return (0);
}

int	ft_pwd(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run pwd\n");
	return (0);
}

int	ft_export(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run export\n");
	return (0);
}

int	ft_unset(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run unset\n");
	return (0);
}

int	ft_env(char **argv, int argc, t_environ *environ)
{
	(void)argv;
	(void)argc;
	(void)environ;
	printf("run env\n");
	return (0);
}

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
