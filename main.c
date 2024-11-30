#include "pipex.h"


int main(int argc,char *argv[],char *envp[])
{

    //Variaveis
    int infile;
    int outfile;
    int child;
    int end[0];

    /* Erro Handler */
    if(argc != 5)
    {
        printf("Number of Arguments not valid\n");
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

    /* STEP EVENT */

    /* Vou ter de conseguir as variaveis para puder usar o execve */
                /*PARSING*/

    char **cmd1;
    char **cmd2;
    cmd1 = ft_split(argv[2]," ");
    cmd2 = ft_split(argv[3]," ");

    if(child == 0)
    { 
        //Estou no evento child
        close(end[0]);

        //Estou a fazer com que o infile fique com o fd de leitura para que possa ser lidas os comandos
        dup2(infile,STDIN_FILENO);
        //Ao acabarmos de executar o comando CMD1, vamos passar o output dela para o pip usando o dup2
        dup2(end[1],STDOUT_FILENO);

        //execve(PATH,ARGS,ENVP);
        close(end[1]);
    }else{
        wait(NULL);
        //Estou no evento pai
    }
}


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