#include "pipex.h"

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

static void	child_process(int end[2], int infile, char *argv[], char *envp[])
{
	close(end[0]);
	dup2(infile, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	close(infile);
	execute(argv, envp, 2);
	exit(EXIT_FAILURE);
}

static void	parent_process(int end[2], int outfile, char *argv[], char *envp[])
{
	wait(NULL);
	close(end[1]);
	dup2(outfile, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(outfile);
	execute(argv, envp, 3);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outfile;
	int	child;
	int	end[2];

	if (argc != 5)
		handle_error("Number of Arguments not valid\n");
	if (access(argv[1], F_OK) == -1)
		handle_error("Infile does not exist\n");
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		handle_error("Error Opening infile or outfile");
	if (pipe(end) == -1)
		handle_error("Error creating the pipe\n");
	child = fork();
	if (child == -1)
		handle_error("Error creating the fork\n");
	if (child == 0)
		child_process(end, infile, argv, envp);
	else
		parent_process(end, outfile, argv, envp);
}