#include "pipex_bonus.h"

int	handle_error(const char *message)
{
	ft_printf(message);
	exit(EXIT_FAILURE);
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
char	*get_command(char **mypaths, char *cmd_arg)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = -1;
	while (mypaths[++i])
	{
		tmp = ft_strjoin(mypaths[i], "/");
		cmd = ft_strjoin(tmp, cmd_arg);
		free(tmp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
	}
	return (NULL);
}

void	execute(char *argv[], char *envp[], int num)
{
	char	*path_from_env;
	char	**mypaths;
	char	**mycmdargs;
	char	*cmd;

	path_from_env = find_path(envp);
	if (!path_from_env)
		exit(EXIT_FAILURE);
	mypaths = ft_split(path_from_env, ':');
	mycmdargs = ft_split(argv[num], ' ');
	cmd = get_command(mypaths, mycmdargs[0]);
	if (cmd)
		execve(cmd, mycmdargs, envp);
	free_error(mypaths, mycmdargs);
}