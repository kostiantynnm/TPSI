#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_MSG_SIZE 1024

int main() {
    
    int fifo1;
    int fifo2;
    int p;
    int n;
    char msg[MAX_MSG_SIZE];

    mkfifo("fifochat1", 0666);
    mkfifo("fifochat2", 0666);

    p = fork();
    if(p<0)
    {
        exit(1);
    }

    else if(p>0) // padre  //scrive
    {
        while(1){
            fifo1 = open("fifochat1", O_WRONLY);
            scanf("%s", msg);
            //fgets(msg, MAX_MSG_SIZE, stdin);
            write(fifo1, msg, strlen(msg)+1);
            close(fifo1);
        }
        
    }
    else  // figlio  //legge
    {
        while(1){
            fifo2 = open("fifochat2", O_RDONLY);
            n = read(fifo2, msg, MAX_MSG_SIZE);
            if(n>0) printf("Received: %s\n", msg);
            close(fifo2);
        }
        
    }
    return 0;
}