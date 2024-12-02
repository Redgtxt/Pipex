#include "pipex.h"


int main(int argc, char *argv[],char *envp[])
{

    int i = 0;
    while(envp[i] != NULL)
    {
        printf("%s\n",envp[i]);
        i++;
    }
}




































    /*
    int infile;
    int outfile;

    infile = open(argv[1], O_RDONLY, 0644);
    if(infile == -1)//!Error Handling
    {
        perror("Error opening infile");
        return 1;
    }

    outfile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(outfile == -1)//!Error Handling
    {
        perror("Error opening outfile");
        return 1;
    }

    int p1[2];
    if(pipe(p1) == -1)//!Error Handling
    {
        perror("Error pipe");
        return 1;
    }

    int child = fork();
    if(child == -1)//!Error Handling
    {
        perror("Error fork");
        return 1;
    }

    if(child == 0)
    {
    // * Estou no child

    // * Vou fechar o fd e abrir o infile no modo leitura
    if(dup2(infile, STDIN_FILENO) == -1)//!Error Handling
    {
        perror("Error dup2 infile");
        return 2;
    }
    
    if(write(p1[1],"Hello",5) == -1)//!Error Handling
    {
        perror("Error write");
        return 2;    
    }

    close(p1[1]);
    }
    else
    { // * Estou no parent

        write(p1[0], "Hello", 5);
        close(p1[0]);
    }

    if(dup2(outfile, STDOUT_FILENO) == -1)
    {
        perror("Error dup2 outfile");
        return 2;
    }

    close(infile);
    execl("/bin/wc", "wc",NULL);
    *
}
*/