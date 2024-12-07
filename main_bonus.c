#include "pipex_bonus.h"

void	free_str_array(char **arr)
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

void	create_here_doc(char *limiter)
{
	int		here_doc;
	char	*line;

	here_doc = open("temp_file", O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
	if (here_doc == -1)
		handle_error_bonus("Error creating the here_doc");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(here_doc, line, ft_strlen(line));
		free(line);
	}
	close(here_doc);
}

int	check_here_doc(t_pipex *p, int argc, char *argv[])
{
	p->is_here_doc = 0;
	if (argc > 1)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			p->is_here_doc = 1;
	}
	return (p->is_here_doc);
}

int	prepare_pipex_files(t_pipex *p, int argc, char *argv[])
{
	check_here_doc(p, argc, argv);
	if ((p->is_here_doc && argc < 6) || (!p->is_here_doc && argc < 5))
		handle_error_bonus("Not enough arguments");
	if (p->is_here_doc)
	{
		create_here_doc(argv[2]);
		p->infile = open("temp_file", O_RDONLY);
		p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		p->infile = open(argv[1], O_RDONLY);
		p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (p->infile < 0 || p->outfile < 0)
		handle_error_bonus("Error opening files");
	return (p->is_here_doc);
}

void	calculate_commands_count(t_pipex *p)
{
	if (p->is_here_doc)
		p->num_commands = p->num_commands - 4;
	else
		p->num_commands = p->num_commands - 3;
}

void	create_pipes(t_pipex *p)
{
	int	i;

	calculate_commands_count(p);
	p->num_pipes = p->num_commands - 1;
	p->pipe_fds = malloc(sizeof(int) * 2 * p->num_pipes);
	if (p->pipe_fds == NULL)
		handle_error_bonus("Error allocating memory for pipes");
	i = 0;
	while (i < p->num_pipes)
	{
		if (pipe(p->pipe_fds + 2 * i) == -1)
			handle_error_bonus("Error creating pipes");
		i++;
	}
}

int	get_command_index(t_pipex *p, int i)
{
	int	command_index;

	if (p->is_here_doc)
		command_index = 3 + i;
	else
		command_index = 2 + i;
	return (command_index);
}

void	spawn_child_process(t_pipex *p, int i, char *argv[], char *envp[])
{
	int	command_index;
	int	child;

	command_index = get_command_index(p, i);
	child = fork();
	if (child < 0)
		handle_error_bonus("Error creating fork");
	if (child == 0)
	{
		if (i == 0)
			setup_first_command(p);
		else if (i == p->num_commands - 1)
			setup_last_command(p, 2 * (i - 1));
		else
			setup_middle_command(p, 2 * (i - 1));
		close_all_pipes(p);
		execute_command(argv, envp, command_index);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;
	int		i;
	int		wait_count;

	p.num_commands = argc;
	prepare_pipex_files(&p, argc, argv);
	create_pipes(&p);
	i = 0;
	while (i < p.num_commands)
	{
		spawn_child_process(&p, i, argv, envp);
		i++;
	}
	close_all_pipes(&p);
	wait_count = p.num_commands;
	while (wait_count > 0)
	{
		wait(NULL);
		wait_count--;
	}
	free(p.pipe_fds);
	if (p.is_here_doc)
		unlink("temp_file");
	return (0);
}
