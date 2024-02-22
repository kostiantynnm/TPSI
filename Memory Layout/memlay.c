#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global1 = 130;
int global2; 
int main()
{
    int a;
    while(1){
        printf("%d \n", getpid());
        printf("%p \n", &a);
        sleep(1);
    }
}

/*
size a.out 
   text    data     bss     dec     hex filename
   1384     604      12    2000     7d0 a.out

objdump -s a.out

objdump -s -j .data a.out

          *pid*
cat /proc/6948/maps


*/