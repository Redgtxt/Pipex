#include "pipex.h"

/*
int main(int argc,char *argv[])
{
  (void) argv;
  (void) argc;
  char *args[2];
  args[0] = "ls";
  args[1] = NULL;
  int pid = fork();
  if(pid == -1)
  {

    return 1;
  }

    if(pid == 0)
    {
      //Child
     int err =  execve("/bin/ls", args, NULL);
      if(err == -1)
      {
        printf("Could not find program to execute\n");
      }
    }else{
      int wstatus;
      int statusCode;
      //PArent
      wait(&wstatus);
      if(WIFEXITED(wstatus))
      {
         statusCode = WEXITSTATUS(wstatus);
         if(statusCode == 0)
          printf("Sucesso\n");
         else
         printf("Falha");
      }
      printf("Some post processing goes here\n");
    }
    return 0;
  }
#include <time.h>
//Two way communication 
int main(void)
{
  
  //5 => 5 * 4 = 20 => 20
  //
  int p1[2]; // vai da child para o parent
  int p2[2]; // vai do parent para a child

  if(pipe(p1) == -1)
  {
    perror("Error pipe");
    return 1;
  }
  
  if(pipe(p2) == -1)
  {
    perror("Error pipe");
    return 1;
  }
  int pid = fork();
  if(pid == -1)
  {
    perror("Erro no fork");
    return 1;
  }

  //CHILD PROCCES
  if(pid == 0)
  {
    close(p1[0]);
    close(p2[1]);
    int x;
    //Vou ler do file descriptor 0 e armazenar o que estiver la em uma variavel
    if(read(p2[0],&x,sizeof(x)) == -1)
    {
      perror("Erro no read");
      return 1;
    }
    printf("Receiveid %d\n",x);
    x *= 4;
   if (write(p1[1],&x,sizeof(x))== -1)
   {
    perror("Erro no write");
    return 1;
   }
   printf("Wrote %d\n",x);
    close(p1[1]);
    close(p2[0]);
  }else{
    close(p1[1]);
    close(p2[0]);
  
    //Parent Process
    srand(time(NULL));
    int y = rand() % 10;
    if(write(p2[1],&y,sizeof(y)) == -1)
    {
      perror("Erro no write");
      return 1;
    }

   // printf("Wrote %d\n",y);
    if(read(p1[0],&y,sizeof(y)) == -1)
    {
          perror("Erro no write");
      return 1;
    }
    printf("Result is %d\n",y);
      close(p1[0]);
    close(p2[1]);
    wait(NULL);
  }
  return 0;
}










MORE PIPES
int main(void)
{
  int arr[] = {1, 2, 3, 4, 1, 2,32,79};
  int arrSize = sizeof(arr) / sizeof(int);
  int start,end;
  int fd[2];

  if(pipe(fd) == -1)
  {
   	perror("Pipe Eroor");
    return 1;
  }

  int child = fork();
  if(child == -1)
  {
    perror("Child eroor");
    return 1;
  }

  if(child == 0)
  {
    start = 0;
    end = arrSize / 2;
  }else{
    //Começa a metade do array
    start = arrSize / 2;
    end = arrSize;
  }
  
  int sum = 0;
  int i;
  for(i = start; i < end;i++)
  {
    sum+=arr[i];
  }
  printf("Calculated partial sum: %d\n",sum);

  if(child == 0)
  {
    close(fd[0]);// Nao estou a usar
    if(write(fd[1],&sum,sizeof(sum)) == -1)
      perror("Erro write");
    close(fd[1]); // Ja usei, vamos  fechar
  }else{
    int sumFromChild;
    close(fd[1]);
    if(read(fd[0],&sumFromChild,sizeof(sumFromChild)) == -1)
      perror("Erro read");
    close(fd[0]);

    int totalSum = sum + sumFromChild;
    wait(NULL);
    printf("Total sum is: %d\n",totalSum);
  }

  return 0;
}


int main(void)
{
  int fd[2];
  //fd[0] - read
  //fd[1] - write
    if(pipe(fd) == -1)
      printf("pipe() failed\n");

    int id = fork();
    if(id == -1)
      printf("fork() failed\n");
    if(id == 0)
      {
          close(fd[0]);
          int x;
          printf("Input a number: ");
          scanf("%d", &x);
          if(write(fd[1], &x, sizeof(int)) == -1)
            printf("write() failed\n");
          close(fd[1]);
      }else{
        close(fd[1]);
        int y;
        //Vamos ler
        if(read(fd[0], &y, sizeof(int)) == -1)
          printf("read() failed\n");
        close(fd[0]);
        printf("Got from the child process %d\n", y);
      }
  return 0;
}

//!getpid,  gettpid functions

int main(void)
{
  int child = fork();
  if(child == 0)
       sleep(1);
  printf("child = %d,dad = %d\n", getpid(),getppid());

  int res = wait(NULL);
        if(res == -1)
          printf("No chielderen to wait for\n");
        else
          printf("Child returned = %d\n", res);//Retorna o id do proccesso
  return 0;

}



int main(void)
{
  int child = fork();
  int n;
  if (child == 0)
    {
    	n = 1;
    }else{
      n = 6;
    }
    if(child != 0)
   	 waitpid(child,NULL,0);
    int i;
    for (i = n; i < n + 5; i++)
      {
      	printf("%d ", i);
        fflush(stdout);
      }
      if (child != 0)//Nao vai executar pq sou a child
	  	printf("\n");
  return 0;
}
*/








//CHILD PROCESS E SEMPRE 0
//int main(void)
//{
//  int id = fork();
//
//  //Se nao estiver mos no child process vou dar fork
//  if(id != 0)
//    {
//    	fork();
//
//    }
//  printf("Hello World!\n");
//
////  if (id == 0)
////    {
////    	printf("I am the child\n");
////    }else
////      {
////      printf("I am the parent\n");
////      }
//  //printf("%d\n", id);
//
//}

/*
int main(void)
{
  printf("Hello World!\n");
  printf("Sou o Pai!\n");
  int child1 = fork();
  int child2 = fork();
  if (child1 == 0)
    {
 	 if (child2 == 0)
    	{
       	printf("We are process Y!\n");
    	}else{
      	printf("We are process X!\n");
		}
	}else{
          if (child2 == 0){
            printf("We are process Z!\n");
          }else{
            printf("We are DAD process!\n");
          }
	}
}


 */
/* !FORK TEST
int main(void)
{
    printf("Estou no parent\n");
  int child = fork();
  printf("child = %d\n", child);
  if (child == 0)
    {
    ft_printf("Estou no child\n");
    exit(0);
    }
    waitpid(child, NULL, 0);
    printf("Acabou\n");
} */

/* !Variaveis Teste Fork
int main() {
  int i = 0;
  int child = fork();
  if(child == 0) {
    printf("child i = %d\n", i);
    exit(0);
  }
  i++;
  printf("Parent i = %d\n", i);
  waitpid(child, NULL, 0);
}
 */

/*
//!Dup2 teste
//!Dup 2 || Vai duplicar um processo, pudendo escolher qual FD quero usar
int main(void)
{
	 int file_desc = open("infile.txt",O_WRONLY | O_APPEND);
	 if(file_desc == -1)
     {
           perror("open");
           exit(1);
     }

    // here the newfd is the file descriptor of stdout (i.e. 1)
    if (dup2(file_desc, 0) == -1)
{
    perror("dup2 failed");  // Exibe erro
    close(file_desc);       // Fecha o arquivo que foi aberto antes
    exit(EXIT_FAILURE);     // Sai com erro
}

    // All the printf statements will be written in the file
    // "infile.txt"
    printf("I will be printed in the Console YUPII\n");
    close(file_desc);
}*/

/*
//!access teste
//! Return 1 se der erro
//! Return 0 se correr tudo bem
int main(void)
{
	if(access("infile.txt",F_OK) == 0)
          printf("File exist\n");
    else
      printf("File doesn't exist\n");
} */
/*
int main()
{
	char *args[3];

	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("This line will not be executed.\n");

	return (0);
} */