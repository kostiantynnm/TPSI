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

    p = fork();
    if(p<0)
    {
        exit(1);
    }

    else if(p>0) // parent  //writes
    {
        while(1){
            fifo2 = open("fifochat2", O_WRONLY);
            scanf("%s", msg);
            //fgets(msg, MAX_MSG_SIZE, stdin);
            write(fifo2, msg, strlen(msg)+1);
            close(fifo2);
        }
    }
    else  // child  //reads
    {
        while(1){
            fifo1 = open("fifochat1", O_RDONLY);
            n = read(fifo1, msg, MAX_MSG_SIZE);
            if(n>0) printf("Received: %s\n", msg);
            close(fifo1);
        }
        
    }
    return 0;
}