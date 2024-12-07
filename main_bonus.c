#include "pipex.h"
#include "string.h"

void	execute_bonus(char *argv[], char *envp[], int num)
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

     if (access(cmd, X_OK) == -1) {
        fprintf(stderr, "Error: %s: command not found\n", mycmdargs[0]);
        exit(EXIT_FAILURE);
    }


	if (cmd)
		  if (execve(cmd, mycmdargs, envp) == -1) {
        perror("execve"); // Print error message and exit
        exit(EXIT_FAILURE);
    }
	free_error(mypaths, mycmdargs);
}

void create_here_doc(char *argv[]) {
    char *limiter = argv[2];
    int here_doc = open("temp_file", O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
    if (here_doc == -1)
        handle_error("Error creating the here_doc");

    char *line;
   while (1) {
    write(1, "heredoc> ", 9);
    line = get_next_line(0);

    // Verifica se CTRL+D foi pressionado (EOF)
    if (!line) {
        break;
    }

    // Verifica o delimitador (LIMITER)
    if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n') {
        free(line);
        break;
    }

    // Escreve no arquivo temporário
    write(here_doc, line, ft_strlen(line));
    free(line);
}
    close(here_doc);
}

int main(int argc, char *argv[], char *envp[])
{
    int is_here_doc = 0;
    int infile, outfile, num_pipes, num_comandos, *end;
    int child, i, j, command_index;

    // Determinar o modo (here_doc ou infile)
    if (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0)
        is_here_doc = 1;

    // Validar argumentos mínimos
    if ((is_here_doc && argc < 6) || (!is_here_doc && argc < 5))
        handle_error("Not enough arguments");

    // Configurar arquivos de entrada e saída
    if (is_here_doc) {
        create_here_doc(argv);
        infile = open("temp_file", O_RDONLY);
        outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644); // Append mode
    } else {
        infile = open(argv[1], O_RDONLY);
        outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644); // Truncate mode
    }

    if (infile < 0 || outfile < 0)
        handle_error("Error opening files");

    // Calcular o número de comandos e pipes
    if (is_here_doc)
        num_comandos = argc - 4;
    else
        num_comandos = argc - 3;

    num_pipes = num_comandos - 1;
    end = malloc(sizeof(int) * 2 * num_pipes);
    if (!end)
        handle_error("Error allocating memory for pipes");

    // Criar os pipes
    i = 0;
    while (i < num_pipes) {
        if (pipe(end + 2 * i) == -1)
            handle_error("Error creating pipes");
        i++;
    }

    // Fork e configuração dos comandos
    i = 0;
    while (i < num_comandos) {
        if (is_here_doc)
            command_index = 3 + i;
        else
            command_index = 2 + i;

        child = fork();
        if (child < 0)
            handle_error("Error creating fork");

        if (child == 0) {
            // Primeiro comando
            if (i == 0) {
                dup2(infile, STDIN_FILENO);
                dup2(end[1], STDOUT_FILENO);
                close(infile);
            }
            // Último comando
            else if (i == num_comandos - 1) {
                dup2(end[2 * (i - 1)], STDIN_FILENO);
                dup2(outfile, STDOUT_FILENO);
                close(outfile);
            }
            // Comandos intermediários
            else {
                dup2(end[2 * (i - 1)], STDIN_FILENO);
                dup2(end[2 * i + 1], STDOUT_FILENO);
            }

            // Fechar todos os pipes no processo filho
            j = 0;
            while (j < 2 * num_pipes) {
                close(end[j]);
                j++;
            }

            // Executar o comando
            execute_bonus(argv, envp, command_index);
        }
        i++;
    }

    // Fechar todos os pipes no processo pai
    j = 0;
    while (j < 2 * num_pipes) {
        close(end[j]);
        j++;
    }

    // Aguardar todos os filhos
    j = 0;
    while (j < num_comandos) {
        waitpid(-1, NULL, 0);
        j++;
    }

    // Limpar
    free(end);
    if (is_here_doc)
        unlink("temp_file");

    printf("Pipeline executed successfully!\n");
    return 0;
}
