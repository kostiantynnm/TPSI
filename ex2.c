//         KOSTIANTYN NAFTULOVYCH 4-E   |07.12.23|  esircizio n2.
#include <stdio.h>        
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char*argv[]) 
{
    char c;

    if(argc < 3) //controllo se utente ha inserito i nomi dei due file
    {
        printf("Hai inserito non abastanza argomenti");
        return 1; //termino la programma con il codice di errore
    }

    FILE *origine, *destinatario; 
    origine = fopen(argv[1], "r"); // aperta del file in modalita read
    destinatario = fopen(argv[2], "w"); // aperta del file in modalita write

    //constrollo se file sono aperti successivamente 
    if(origine == NULL) 
    { 
        printf("File origine non è aperto\n"); 
        exit(1);//termino la programma con il codice di errore
    }
    if(destinatario == NULL)
    { 
        printf("File destinatario non è aperto\n"); 
        exit(1);//termino la programma con il codice di errore
    }

    //ciclo che prente i simboli dal file origine e le scrive dentro il file destonatario
    do { 
        c = fgetc(origine);
        fputc(c, destinatario);
    }while (c != EOF); //finche non arriva alla fine del file
    
    //chido i file aperti
    fclose(origine); 
    fclose(destinatario); 

    return 0;
}