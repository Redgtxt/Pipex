#include "pipex.h"

int	handle_error(const char *message)
{
	perror(message);
	return (-1);
}

char	*find_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (envp[i] + 5);
		}
		i++;
	}
	return (NULL);
}

void	free_error(char **mypaths, char **mycmdargs)
{
	int	i;

	i = -1;
	while (mypaths[++i])
		free(mypaths[i]);
	free(mypaths);
	i = -1;
	while (mycmdargs[++i])
		free(mycmdargs[i]);
	free(mycmdargs);
	exit(EXIT_FAILURE);
}
