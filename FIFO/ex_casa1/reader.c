// 2_fifo_Consumatore.c

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
    int sum = 0;
    int i;

    // Apertura della FIFO in lettura
    sum_fifo = open(FIFO_NAME, O_RDONLY);

    // Lettura dei numeri dalla FIFO
    printf("Consumatore: Lettura dei numeri dalla FIFO...\n");
    for (i = 0; i < NUMBERS_TO_GENERATE; i++) {
        read(sum_fifo, &numbers[i], sizeof(int));
        printf("Numero letto: %d\n", numbers[i]);
        sum += numbers[i];
    }

    // Calcolo e visualizzazione della somma
    printf("Consumatore: Somma dei numeri: %d\n", sum);

    // Chiusura della FIFO
    close(sum_fifo);

    // Rimozione della FIFO
    unlink(FIFO_NAME);

    return 0;
}
