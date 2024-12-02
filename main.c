#include "pipex.h"

char *find_path(char *envp[])
{
    int i = 0;

    while (envp[i]) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0) {
            return (envp[i] + 5); // Retorna o valor de PATH sem "PATH="
        }
        i++;
    }
    return (NULL); // Caso PATH não seja encontrado
}

void free_error( char **mypaths,char **mycmdargs)
{
    int i;

       i = -1;
    while (mypaths[++i])
        free(mypaths[i]);
    free(mypaths);

    i = -1;
    while (mycmdargs[++i])
        free(mycmdargs[i]);
    free(mycmdargs);

    exit(EXIT_FAILURE);
}

void execute(char *argv[], char *envp[], int num)
{
    char *PATH_from_env = find_path(envp);
    if (!PATH_from_env)
        exit(EXIT_FAILURE);
    
    char **mypaths = ft_split(PATH_from_env, ':');
    char **mycmdargs = ft_split(argv[num], ' ');
    int i = -1;

    while (mypaths[++i]) {
        char *tmp = ft_strjoin(mypaths[i], "/");
        char *cmd = ft_strjoin(tmp, mycmdargs[0]);
        free(tmp);
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, mycmdargs, envp);
            perror("Execve failed");
        }
        free(cmd);
    }
    free_error(mypaths,mycmdargs);
}



int main(int argc,char *argv[],char *envp[])
{

    //Variaveis
    int infile;
    int outfile;
    int child;
    int end[2];

    /* Erro Handler */
    if(argc != 5)
    {
        printf("Number of Arguments not valid\n");
        return -1;
    }
    
    if(access(argv[1],F_OK) == -1)
    {
        printf("Vou dar erro porque o infile nao existe\n");
        return -1;
    }

    
    infile = open(argv[1],O_RDONLY);
    outfile = open(argv[4],O_CREAT | O_RDWR | O_TRUNC, 0644);


    /* Erro Handler */
    if(infile < 0 || outfile < 0) 
        return -1;

    /* Erro Handler */
    if(pipe(end) == -1)
    {
        printf("Error creating the pipe\n");
        return -1;
    }
    
    child = fork();
    /* Erro Handler */
    if(child == -1)
    {
        printf("Error creating the fork\n");
        return -1;
    }


    if(child == 0)
    { 
        //Estou no evento child
        close(end[0]);
        //Estou a fazer com que o infile fique com o fd de leitura para que possa lidas os comandos
        dup2(infile,STDIN_FILENO);
        //Ao acabarmos de executar o comando CMD1, vamos passar o output dela para o pip usando o dup2
        dup2(end[1],STDOUT_FILENO);
        close(end[1]);
        close(infile);
        execute(argv,envp,2);

        exit(EXIT_FAILURE);
    }else
       { //Estou no evento pai
        wait(NULL);
        close(end[1]);
        //Estou a fazer com que o outfile fique com o fd de escrita para que possa escrever os comandos
        dup2(outfile,STDOUT_FILENO);
        //Q
       dup2(end[0],STDIN_FILENO);
       
       close(end[0]);
       close(outfile);
        execute(argv,envp,3);
        exit(EXIT_FAILURE);
    }
}


/*
    TEHNO DE VERIFICAR SE OS CMD1 E CMD2 SAO ARGUMENTOS VALIDOS
*/

/*
    execve Arguments

    PATH -- Path do comando: bin/ls
    ARGS -- Array de argumentos que vao ser executados(tem de terminar no NULL)
    ENVP -- An array of pointers to null-terminated strings representing the environment variables for the new program. It is also null-terminated. 
*/


/* NOTAS IMPORTANTES

File Descriptor	Constante	Descrição
0	STDIN_FILENO	Entrada padrão (teclado, por padrão)
1	STDOUT_FILENO	Saída padrão (tela, por padrão)
2	STDERR_FILENO	Saída de erro padrão (tela, por padrão)

end[0]: lado de leitura do pipe.
end[1]: lado de escrita no pipe.


O fork() cria dois processos:
Child (filho): executa cmd1.
Parent (pai): executa cmd2.

Redireciona a entrada de dados (stdin) para o arquivo infile usando dup2().->   O primeiro comando(cmd 1) precisa receber dados do infile
                                                                                Dou dup para simular a leitura de um arquivo

 Redireciona a saída de cmd1 para o lado de escrita do pipe (end[1]) usando dup2()-> Tenho de enviar o output do comando cmd1 para o cmd2 atraves de um pipe usando o dup2

*/