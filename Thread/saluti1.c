#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

//Thread
//POSIX - una standart di UNIX
void* StampaBuongiorno(void* par){
    printf("Buongiorno\n");
    return NULL;
}
void* StampaBuonasera(void* par){
    printf("Buonasera\n");
    return NULL;
}
void* StampaBuonanotte(void* par){
    printf("Buonanotte\n");
    return NULL;
}

int main(){

    pthread_t threadGiorno, threadSera, threadNotte;

    printf("Ciao\n");

    pthread_create(&threadGiorno, NULL, &StampaBuongiorno, NULL);
    pthread_create(&threadSera, NULL, &StampaBuonasera, NULL);
    pthread_create(&threadNotte, NULL, &StampaBuonanotte, NULL);

    pthread_join(threadGiorno, NULL);
    pthread_join(threadSera, NULL);
    pthread_join(threadNotte, NULL);

    //printf("Buongiorno\n");
    //printf("Buonasera\n");
    //printf("Buonanotte\n");

    return 0;
}

// gcc saluti1.c -o saluti1 -lpthread
