#include "pipex_bonus.h"

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
