#include "pipex_bonus.h"

void handle_error_bonus(const char *message)
{
    ft_putstr_fd((char *)message, STDERR_FILENO);
    ft_putstr_fd((char *)"\n", STDERR_FILENO);
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

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_split_arrays(char **mypaths, char **mycmdargs)
{
	free_str_array(mypaths);
	free_str_array(mycmdargs);
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

