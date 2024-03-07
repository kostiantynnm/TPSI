#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#define DIM_BUFFER 1024

//#include <fcntl.h>


typedef struct 
{
    char marca[32];
    char modello[64];
    int  pixels;  
}Smartphone;



int main(int argc, char*argv[]) // Naftulovych Kostiantyn 4E      Fila - B    //10:39
{
    int p, fd[2], status, n;
    Smartphone phone;
    FILE *dati;
    unsigned char buffer[DIM_BUFFER];

    if(pipe(fd) == -1)
    {
        printf("Errore di creazione di una pipe");
        exit(1);
    }

    p = fork();
    
    if(p<0)
    {
        printf("Errore di creazione di una fork");
        exit(1);
    }    
    if (p>0) // padre
    {
        char c;

        close(fd[0]);   
        printf("Marca: ");                                        //passa gli dati al processo figlio
        scanf("%s",phone.marca);
        printf("Modello: ");
        scanf("%s",phone.modello);
        printf("Pixel: ");
        scanf("%d",&phone.pixels);
        write(fd[1], phone.marca, sizeof(phone.marca));
        write(fd[1], phone.modello, sizeof(phone.modello));
        write(fd[1], &phone.pixels, sizeof(phone.pixels));

        close(fd[1]);
        wait(&status);

        dati = fopen(argv[1], "rb");
        while(fread(buffer, 1, DIM_BUFFER, dati)!= 0)
        {
            printf("%s\n", buffer);
        }
        fclose(dati);
    }
    else  //figlio
    {
        close(fd[1]);
        dati = fopen(argv[1], "wb");
        if(dati == NULL) 
        {
            close(fd[0]);
            return 0;
        }
        while(read(fd[0], buffer, sizeof(buffer)))
        {   
            
            fwrite(buffer, 1, n, dati);
        }
        while(read(fd[0], buffer, sizeof(buffer)))
        {   
            
            fwrite(buffer, 1, n, dati);
        }
        close(fd[0]);
        fclose(dati);
    }
}