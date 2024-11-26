#include "pipex.h"

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