#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#define DIM_BUFFER 1024

typedef struct {
    char marca[32];
    char modello[64];
    int pixels;  
} Smartphone;

int main(int argc, char* argv[]) {
    int p, fd[2], status;
    Smartphone phone;
    FILE *dati;
    unsigned char buffer[DIM_BUFFER];

    if(pipe(fd) == -1) {
        printf("Errore di creazione di una pipe");
        exit(1);
    }

    p = fork();
    
    if(p < 0) {
        printf("Errore di creazione di una fork");
        exit(1);
    }    
    if (p > 0) { // parent
        close(fd[0]);   
        printf("Marca: ");
        scanf("%s", phone.marca);
        printf("Modello: ");
        scanf("%s", phone.modello);
        printf("Pixel: ");
        scanf("%d", &phone.pixels);
        write(fd[1], &phone, sizeof(phone));
        close(fd[1]);
        wait(&status);

        dati = fopen(argv[1], "rb");
        while(fread(buffer, 1, DIM_BUFFER, dati) != 0) {
            fwrite(buffer, 1, DIM_BUFFER, stdout); // print buffer to stdout
        }
        fclose(dati);
    } else { // child
        close(fd[1]);
        dati = fopen(argv[1], "wb");
        if(dati == NULL) {
            close(fd[0]);
            return 0;
        }
        while(read(fd[0], buffer, sizeof(buffer)) > 0) {
            fwrite(buffer, 1, sizeof(buffer), dati);
        }
        close(fd[0]);
        fclose(dati);
        exit(0);
    }
}
