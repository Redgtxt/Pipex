#include "pipex_bonus.h"


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