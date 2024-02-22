// 2_fifo_Produttore.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "sum"
#define NUMBERS_TO_GENERATE 5

int main() {
    int numbers[NUMBERS_TO_GENERATE];
    int sum_fifo;
    int i;

    // Creazione della FIFO
    mkfifo(FIFO_NAME, 0666);

    // Apertura della FIFO in scrittura
    sum_fifo = open(FIFO_NAME, O_WRONLY);

    // Generazione dei numeri casuali e inserimento nella FIFO
    printf("Produttore: Generazione di %d numeri casuali...\n", NUMBERS_TO_GENERATE);
    for (i = 0; i < NUMBERS_TO_GENERATE; i++) {
        numbers[i] = rand() % 100;
        printf("Numero generato: %d\n", numbers[i]);
        write(sum_fifo, &numbers[i], sizeof(int));
    }

    // Chiusura della FIFO
    close(sum_fifo);

    return 0;
}
