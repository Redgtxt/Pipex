#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
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


void handle_error_bonus(const char *message);
char	*find_path(char *envp[]);
void	free_error(char **mypaths, char **mycmdargs);
char	*get_command(char **mypaths, char *cmd_arg);
void	execute(char *argv[], char *envp[], int num);
void	execute_bonus(char *argv[], char *envp[], int num);
#endif
