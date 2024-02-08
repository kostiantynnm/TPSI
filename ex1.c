#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main()
{
    int p;
    int fd[2];
    //char buffer[BUFFER_SIZE];
    int n;

    if(pipe(fd) == -1)
    {
        printf("Errore pipe");
        exit(-1);
    }

    p = fork();

    if(p<0) printf("Errore fork");

    if(p>0) //padre
    {
        printf("il processo padre: il mio PID = %d. mio figlio ha PID = %d\n", getpid(), p);
        close(fd[0]); //padre chiude la pipe in lettura

        const char* messaggio = "Buona fortuna";
        if(write(fd[1], messaggio, strlen(messaggio))==-1)
        {
            printf("\nErrore di scrittura nella pipe");
            close(fd[1]);
            exit(-1);
        }
        close(fd[1]);
        wait();
    }
    else //figlio
    {
        char buffer[BUFFER_SIZE];
        printf("il processo figlio: il mio PID = %d. mio padre ha PID = %d\n", getpid(), getppid());
        close(fd[1]);
        n = read(fd[0], buffer, BUFFER_SIZE);
        if(n==-1)
        {
            printf("\nErrore nella lettura della pipe");
            close(fd[0]);
            exit(-1);
        }
        else buffer[n] = '\0';
        printf("\n Messaggio letto: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}