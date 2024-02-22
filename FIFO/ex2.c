#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <fcntl.h> 


int main()
{
    int fd;
    
    if(mkfifo("myfifo1", 0777) == -1)
    {
        if(errno!=EEXIST)
        {
            printf("Errore nella creazione della FIFO");
            return 1;
        }
    }
}