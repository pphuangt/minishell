#include "minishell.h"

char	*generate_file(void)
{
	static int	i = 0;
	char		*filename;
	char		*id;

	id = ft_itoa(i++);
	if (!id)
		return (err_ret("malloc"), NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", id);
	if (!filename)
		err_ret("malloc");
	return (free(id), filename);
}

void	remove_file(char *filename)
{
	struct stat	path_stat;

	if (stat(filename, &path_stat) == -1)
		return ;
	unlink(filename);
}
