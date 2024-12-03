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
        while (1) {
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
        printf("Vou usar o meu código normal\n");
    }
}

/*

<<: Entrada de texto do terminal redirecionada para o arquivo temporário.
>>: Acrescentar (append) ao invés de sobrescrever o conteúdo do arquivo.


[X] O programa esta a passar se colocar mais um c no here_doc
[]  Ligar com pipe

Parte 2: Ler a entrada do usuário
Exiba uma mensagem no terminal pedindo a entrada (heredoc>).---
Use uma função como get_next_line() ou read() para capturar as linhas digitadas pelo usuário.
Verifique a cada linha se o LIMITER foi digitado.
Se a linha for igual ao LIMITER, pare de capturar a entrada.
Se a linha for válida, escreva no arquivo temporário.
Feche o arquivo temporário após terminar de capturar todas as linhas.

    So vou querer ativar o codigo acima se conter o nome here_doc || DONE

    1. Criar um arquivo temporário
No código, você cria um arquivo temporário para armazenar as linhas digitadas pelo usuário.

2. Ler as linhas do terminal (stdin)
Use uma função como get_next_line() ou read() para capturar as linhas digitadas.

3. Parar ao encontrar o LIMITER
Compare cada linha com o delimitador (LIMITER). Se forem iguais, finalize o processo.
-------------------------------------------------
4. Usar o arquivo temporário como entrada
O arquivo temporário substitui o file1 no restante do pipeline normal.


------------------------------------------------------------------------------
Parte 1: Criar um arquivo temporário
Decida o nome do arquivo temporário (fixo ou gerado dinamicamente, como temp_file_XXXXXX).
Crie o arquivo temporário utilizando open() ou mkstemp().
Configure as permissões do arquivo (ex.: 0644).
Certifique-se de lidar com erros ao criar o arquivo (ex.: perror()).
Feche o arquivo após terminar a criação, mas mantenha o nome para futuras operações.


*/