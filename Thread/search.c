#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

int array[1000];

void* Search(void* par){
    int* params = (int*)par;
    int start = params[0];
    int end = params[1];
    int value = params[2];
    //printf("start = %d, end = %d \n", start, end);
    for(int i = start; i < end; i++)
    {
        if(array[i] == value)
        {
            //printf("Numero %d è trovato in posizione %d\n", value, i);
            //return NULL;
            return (void*)(intptr_t)i;
        }
    }
    //printf("Numero non è trovato\n");
    return NULL;
}

int main(){
    int numtosearch;
    scanf("%d", &numtosearch);
    for(int i = 0; i < 1000; i++)
    {
        array[i] = rand() % 500;
    }
    pthread_t thread1, thread2, thread3, thread4;
    printf("Ciao\n");

    int params1[3] = {0, 250, numtosearch};

    int params2[3] = {250, 500, numtosearch};

    int params3[3] = {500, 750, numtosearch};

    int params4[3] = {750, 1000, numtosearch};


    pthread_create(&thread1, NULL, &Search, params1);

    pthread_create(&thread2, NULL, &Search, params2);

    pthread_create(&thread3, NULL, &Search, params3);

    pthread_create(&thread4, NULL, &Search, params4);

    void* result[4];
    pthread_join(thread1, &result[0]);
    pthread_join(thread2, &result[1]);
    pthread_join(thread3, &result[2]);
    pthread_join(thread4, &result[3]);
    for(int i = 0; i < 4; i++)
    {
        if (result[i] != NULL) {

            printf("Number found at index %ld\n", (intptr_t)result[i]);
        } 
        else {

            printf("Number not found\n");
        }
    }
    
    return 0;
}
