#include "pipex.h"

void parsing(char *envp[],char *argv[])
{
    char **PATH_from_envp;
    char **mypaths;
    char **mycmdargs;
    
    //Vou apanhar a linha do PATH atraves do meu ENVP
    PATH_from_envp = ft_substr(envp,0,ft_strlen(envp));
    mypaths = ft_split(PATH_from_envp,":");

    mycmdargs = ft_split(argv[2]," ");

}

void child_process(int infile,char *cmd1,int p1[2])
{
    if(dup2(infile,STDIN_FILENO) == -1)
    {
        printf("Erro ao fazer dup do infile\n");
    }
    if(dup2(p1[1],STDOUT_FILENO) == -1)
    {
        printf("Erro ao fazer dup no Pipe dentro do child process\n");
    }
    close(p1[0]);
    close(infile);
   // execv(cmd,);//FUNCAO AQUI EXECVE
    exit(EXIT_FAILURE);//SO VAI RODAR CASO NAO CONSIGA ATIVAR O EXECV
}

void parent_process(int outfile, char *cmd2,int p1[2])
{
    int status;

    waitpid(-1,&status,NULL);
    if(dup2(outfile,STDOUT_FILENO) == -1)
    {
        printf("Erro ao fazer dup no parent process\n");
    }
    if(dup2(p1[0],STDIN_FILENO) == -1)
    {
        printf("Erro ao fazer dup no Pipe dentro do parent process\n");
    }
    close(p1[1]);
    close(outfile);
        //execv();//FUNCAO AQUI EXECVE
    exit(EXIT_FAILURE);//SO VAI RODAR CASO NAO CONSIGA ATIVAR O EXECV
}


void pipex(int infile, int outfile,char *cmd1,char *cmd2)
{
    int p1[2];
    int child;
    
    //! Inicializo o Pipe
    if(pipe(p1) == -1)
    {
        printf("Erro no pipe\n");
    }
    child = fork();
    if(child == -1)
    {
        printf("Erro ao inicializar o fork\n");
    }

    if(child == 0)
        child_process(infile,cmd1,p1);
    else
        parent_process(outfile,cmd2,p1);
}
int main(int argc,char *argv[],char *envp[])
{
    int infile;
    int outfile;

    infile = open(argv[1],O_RDONLY);
    outfile = open(argv[4],O_CREAT | O_RDWR | O_TRUNC,0644);
    if(infile < 0 || outfile < 0)
        return -1;
    pipex(infile,outfile,argv,envp);
}

/*
int main(int argc,char *argv[])
{
    if(argc != 5)
    {
        printf("Error: Invalid number of arguments\n");
        return 1;
    }

    char *infile = argv[1];
    char *cmd1 = argv[2]; //Comando 1
    char *cmd2 = argv[3]; //Comando 2
    char *outfile = argv[4];

    printf("Infile: %s\n",infile);
    printf("Cmd1: %s\n",cmd1);
    printf("Cmd2: %s\n",cmd2);
    printf("Outfile: %s\n",outfile);

    return 0;
}
*/