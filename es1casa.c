#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define DIM_ARRAY 1024
int main(int argc, char* argv[])
{
    FILE *file;
    unsigned char buffer[DIM_ARRAY];
    int n;
    int p, status;
    int fd[2];

    if(pipe(fd) < 0) return 0;


    p = fork();
    if(p<0) 
    {
        printf("Errore fork");
        close(fd[0]);
        close(fd[1]);
        return 0;
    }   
    if(p>0) //padre
    {
        close(fd[0]);
        file = fopen(argv[1], "rb");
        if(file == NULL) //errore
        {
            close(fd[1]);
            wait(&status);
            return 0;
        }
        while((n = fread(buffer, 1, sizeof(buffer), file))>0)
            write(fd[1], buffer, n);
        fclose(file);
        close(fd[1]);
        wait(&status);
        return 1;
    }
    else //figlio
    {
        close(fd[1]);
        file = fopen(argv[2], "wb");
        if(file == NULL) //errore
        {
            close(fd[0]);
            return 0;
        }
        while((n = read(fd[0], buffer, sizeof(buffer)))>0)
            fwrite(buffer, 1, n, file);
        fclose(file);
        close(fd[0]);
        return 1;
    }
}