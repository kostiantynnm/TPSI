#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

//Thread
//POSIX - una standart di UNIX
void* StampaBuongiorno(void* par){
    printf("%s\n", (char*)par);
    return NULL;
}
void* StampaBuonasera(void* par){
    printf("%s\n", (char*)par);
    return NULL;
}
void* StampaBuonanotte(void* par){
    printf("%s\n", (char*)par);
    return NULL;
}

int main(){

    pthread_t threadGiorno, threadSera, threadNotte;
    char* msg1 = "boungiorno";
    char* msg2 = "bounasera";
    char* msg3 = "bounanotte";
    printf("Ciao\n");

    pthread_create(&threadGiorno, NULL, &StampaBuongiorno, msg1);
    pthread_create(&threadSera, NULL, &StampaBuonasera, msg2);
    pthread_create(&threadNotte, NULL, &StampaBuonanotte, msg3);

    pthread_join(threadGiorno, NULL);
    pthread_join(threadSera, NULL);
    pthread_join(threadNotte, NULL);

    //printf("Buongiorno\n");
    //printf("Buonasera\n");
    //printf("Buonanotte\n");

    return 0;
}

// gcc saluti1.c -o saluti1 -lpthread
