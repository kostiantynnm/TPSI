#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SLICE_DIM 64
#define NUM_SLICES 16

int write_index;
int read_index;
int n_slices;
pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;


typedef struct {
    unsigned char bufferInStruct[SLICE_DIM];
    int n;
} bufferStruct;

bufferStruct buffer[NUM_SLICES];

void* writeFile(void* arg){
    pthread_mutex_lock(&mutex);
    if(n_slices >= 0)
    {
        fwrite(buffer[read_index].bufferInStruct, 1, buffer[read_index].n, (FILE*)arg);
        read_index = (read_index+1) % NUM_SLICES;
        n_slices--; 
    }
    else{
        pthread_cond_wait(&not_empty, &mutex);
    }
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
}

void* readFile(void* arg){
    int n;
    pthread_mutex_lock(&mutex);
    if(n_slices >= NUM_SLICES)
        pthread_cond_wait(&not_full, &mutex);
    n = fread(buffer[write_index].bufferInStruct, 1, SLICE_DIM, (FILE*)arg);
    if(n > 0){
        buffer[write_index].n = n;
        write_index = (write_index+1) % NUM_SLICES;
        n_slices++;
        pthread_cond_signal(&not_empty);
    }
    pthread_mutex_lock(&mutex);
}

int main(){
    FILE *fr;
    FILE *fw;
    pthread_t writeTh, readTh;

    fr = fopen("origine", 'rb');
    pthread_create(&writeTh, NULL, &writeFile, NULL);
    pthread_create(&readTh, NULL, &readFile, NULL);

    return 0;
}