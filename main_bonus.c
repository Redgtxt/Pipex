#include "pipex.h"
#include "string.h"
//here_doc

void create_here_doc(int argc,char *argv)
{
    
        if (ft_strlen(argv[1]) != 8) 
            handle_error("here_doc is not well written");
         
        if (argc < 3)
            handle_error("You need to use a Limiter");

        char *limiter = argv[2];
        int here_doc = open("temp_file", O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
        if (here_doc == -1)
            handle_error("Error creating the here_doc");

        char *line;
        while (1)
        {
            write(1, "heredoc> ", 9);
            line = get_next_line(0);

            if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n') {
                free(line);
                break;
        }

            write(here_doc, line, ft_strlen(line));
            free(line);
        }
        close(here_doc);
}

int main(int argc,char *argv[],char *envp[])
{
    int is_here_doc = (argc > 1 && ft_strncmp(argv[1],"here_doc",8) == 0);
    int infile;
    int flag;

    flag = 1;

    if(is_here_doc)
    {
        
    }




    if (is_here_doc) 
    {
        create_here_doc(argc,argv);
    } else {
        // Código normal
        if(argc < 5)
            handle_error("Not enought arguments");
        
        //Variaveis
        int outfile;
        int num_pipes;
        int child;
        int num_comandos;

        num_comandos = argc - 3;
        num_pipes = num_comandos - 1;// -1 para saber numero de pipes
        int end[2 * num_pipes];
        infile = open(argv[1], O_RDONLY);
	    if (infile < 0)
		    handle_error("Error Opening infile");
	    outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
          if ( outfile < 0)
		    handle_error("Error Opening outfile");
        
        //Vou criar um loop para criar os pipes
        int i;
        i = 0;
        while (num_pipes > i)
        {
            if(pipe(end + 2 * i) == -1)
                handle_error("Eroor Creating Pipes");
            i++;
        }
        
i = 0; // Índice dos processos

while (num_comandos > i) {
     child = fork();
    if (child < 0)
        handle_error("Error Creating the fork");

    // No processo filho
    if (child == 0) {
        // Primeiro comando
        if (i == 0) {
            dup2(infile, STDIN_FILENO);          // Redirecionar entrada para o arquivo
            dup2(end[1], STDOUT_FILENO);        // Redirecionar saída para o pipe
        } 
        // Último comando
        else if (i == num_comandos - 1) {
            dup2(end[2 * (i - 1)], STDIN_FILENO); // Redirecionar entrada para o último pipe
            dup2(outfile, STDOUT_FILENO);        // Redirecionar saída para o arquivo de saída
        } 
        // Comandos intermediários
        else {
            dup2(end[2 * (i - 1)], STDIN_FILENO); // Redirecionar entrada para o pipe anterior
            dup2(end[2 * i + 1], STDOUT_FILENO); // Redirecionar saída para o próximo pipe
        }
       int j;
        // Fechar todos os extremos dos pipes no processo filho
        j = 0;
        while (2 * (num_comandos - 1) > j)
        {
        close(end[j]);
        j++;
        }

        // Executar o comando usando a função execute
        execute(argv, envp, 2 + i);
    }

    // No processo pai
    i++;
}

// No processo pai: fechar todos os pipes após criar os filhos

int j;
j = 0;
while (2 * (num_comandos - 1) > j)
{
    close(end[j]);
   j++;
}


// Aguardar todos os processos filhos
j = 0;
while ( num_comandos > j) {
    waitpid(-1, NULL, 0);
    j++;
}

printf("Pipeline executado com sucesso!\n");

}
}

/*

[]Fazer execute
[] wait pai

2. Configuração dos Pipes
Determinar quantos pipes serão necessários:
    []O número de pipes é igual ao número de comandos menos 1 (n - 1).
    []Criar um array para armazenar os descritores dos pipes.
    []Criar os pipes necessários:
    []Para cada comando, configure um pipe que conecte a saída de um comando à entrada do próximo.


[]fazer o programa rodar com multiplos pipes
[X]codigo do here_doc esta feito


<<: Entrada de texto do terminal redirecionada para o arquivo temporário.
>>: Acrescentar (append) ao invés de sobrescrever o conteúdo do arquivo.


[X] O programa esta a passar se colocar mais um c no here_doc
[]  Ligar com pipe

3. Gerenciar os Processos
Para cada comando na sequência (cmd1 até cmdn):
Criar um processo filho com fork.
No processo filho:
Configurar o redirecionamento de entrada e saída:
Primeiro comando:
Redirecionar a entrada para o arquivo file1.
Redirecionar a saída para o write do primeiro pipe.
Comandos intermediários:
Redirecionar a entrada para o read do pipe anterior.
Redirecionar a saída para o write do próximo pipe.
Último comando:
Redirecionar a entrada para o read do último pipe.
Redirecionar a saída para o arquivo file2.
Fechar todos os descritores de pipes no processo filho.
Executar o comando atual.
No processo pai:
Continuar para o próximo comando no loop.
Fechar os extremos do pipe usados pelo comando atual.
4. Finalizar no Processo Pai
Fechar todos os pipes após criar os processos filhos.
Aguardar a conclusão de todos os processos filhos usando wait ou waitpid.
*/