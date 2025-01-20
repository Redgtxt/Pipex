#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex {
	int		infile;
	int		outfile;
	int		is_here_doc;
	int		num_commands;
	int		num_pipes;
	int		*pipe_fds;
}	t_pipex;

//utils
void handle_error_bonus(const char *message);
char	*find_path(char *envp[]);
void	free_split_arrays(char **mypaths, char **mycmdargs);
char	*get_command(char **mypaths, char *cmd_arg);

//pipes
void	setup_first_command(t_pipex *p);
void	setup_last_command(t_pipex *p, int pipe_index);
void	setup_middle_command(t_pipex *p, int pipe_index);
void	execute_command(char *argv[], char *envp[], int command_index);
void	close_all_pipes(t_pipex *p);

//here_doc
void	create_here_doc(char *limiter);
int	check_here_doc(t_pipex *p, int argc, char *argv[]);
int	prepare_pipex_files(t_pipex *p, int argc, char *argv[]);
void	calculate_commands_count(t_pipex *p);

void	create_pipes(t_pipex *p);
int	get_command_index(t_pipex *p, int i);
void	spawn_child_process(t_pipex *p, int i, char *argv[], char *envp[]);
#endif
