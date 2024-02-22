#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h> //PER FIFO
int main()
{
    //Dichiarazione della var
    int fd;

    //Creazione FIFO
    //        *nome     *permessi: proprietario, al gruppo, ai tutti gli utenti
    if(mkfifo("myfifo1", 0777) == -1)
    {
        if(errno!=EEXIST)
        {
            printf("Errore nella creazione della FIFO");
            return 1;
        }
    }

    //apro la FIFO in scrittura 
    fd = open("myfifo1", O_WRONLY); //fd = 1 perche la FIFO e aperta in scrittura
    printf("\n aperto la FIFO");

    int x = 90;
    if(write(fd, &x, sizeof(x))==-1)
    {
        printf("Errore in scrittura nella FIFO");
        return 2;
    }
    printf("\n Ho scritto nella FIFO");

    close(fd);

    return 0;
}