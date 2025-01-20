#include "pipex_bonus.h"


void	setup_first_command(t_pipex *p)
{
	dup2(p->infile, STDIN_FILENO);
	dup2(p->pipe_fds[1], STDOUT_FILENO);
	close(p->infile);
}

void	setup_last_command(t_pipex *p, int pipe_index)
{
	dup2(p->pipe_fds[pipe_index], STDIN_FILENO);
	dup2(p->outfile, STDOUT_FILENO);
	close(p->outfile);
}

void	setup_middle_command(t_pipex *p, int pipe_index)
{
	dup2(p->pipe_fds[pipe_index], STDIN_FILENO);
	dup2(p->pipe_fds[pipe_index + 3], STDOUT_FILENO);
}

void	execute_command(char *argv[], char *envp[], int command_index)
{
	char	*path_from_env;
	char	**mypaths;
	char	**mycmdargs;
	char	*cmd;

	path_from_env = find_path(envp);
	if (path_from_env == NULL)
		handle_error_bonus("Path not found in environment");
	mypaths = ft_split(path_from_env, ':');
	mycmdargs = ft_split(argv[command_index], ' ');
	cmd = get_command(mypaths, mycmdargs[0]);
	if (cmd == NULL || access(cmd, X_OK) == -1)
	{
		handle_error_bonus("Command is not valid");
		free_split_arrays(mypaths, mycmdargs);
	}
	if (execve(cmd, mycmdargs, envp) == -1)
	{
		handle_error_bonus("execve failed");
		free_split_arrays(mypaths, mycmdargs);
	}
	free_split_arrays(mypaths, mycmdargs);
}

void	close_all_pipes(t_pipex *p)
{
	int	j;

	j = 0;
	while (j < 2 * p->num_pipes)
	{
		close(p->pipe_fds[j]);
		j++;
	}
}
