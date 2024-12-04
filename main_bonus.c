#include "pipex.h"
#include "string.h"
//here_doc
int main(int argc,char *argv[])
{
    int is_here_doc = (argc > 1 && ft_strncmp(argv[1],"here_doc",8) == 0);
    if (is_here_doc) 
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
    } else {
        // Código normal
        if(argc <= 5)
            handle_error("Not enought arguments");
        
        //Variaveis
        int infile;
        int outfile;
        int num_pipes;
        num_pipes = argc - 3;
        int end[2 * (argc - 1)];

        infile = open(argv[1], O_RDONLY);
	    if (infile < 0)
		    handle_error("Error Opening infile");
	    outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
          if ( outfile < 0)
		    handle_error("Error Opening outfile");
        
        //Vou fazer pipe depedendo da minha quantidade de argumentos
        int i;
        i = 0;
        while(argc - 1 > i)
        {
            if(pipe(end) == -1)
                handle_error("Eror creating Pipe");
            i++;
        }
        printf("Codigo Rodado ate aqui!!!");
    }
}

/*

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