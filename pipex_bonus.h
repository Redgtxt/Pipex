#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

int		handle_error(const char *message);
char	*find_path(char *envp[]);
void	free_error(char **mypaths, char **mycmdargs);
char	*get_command(char **mypaths, char *cmd_arg);
void	execute(char *argv[], char *envp[], int num);

#endif
