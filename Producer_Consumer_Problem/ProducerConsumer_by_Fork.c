#include "pthread.h"
#include "stdio.h"
#include <stdio.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include "unistd.h"
#include "string.h"
#include <time.h>
#include <semaphore.h>

#define M 100 //iterations

//made a struct of shared variables
struct Shared_variables{
    int current_index;
    int buffer[5];
    sem_t space_left, is_filled, mutex; //the three semaphores
    int flag1; //flag when producer iterations ends to notify consumer to not wait for producer to insert items.
};

struct Shared_variables* sharedPointer;

void* producer(){
    for(int i = 0; i < M; i++){

        sem_wait(&(sharedPointer->space_left));
        sem_wait(&(sharedPointer->mutex));

        //producer makes random number as object and inserts in buffer
        int object = rand()%100;
        sharedPointer->buffer[sharedPointer->current_index] = object;
        printf("Produced %d \n",object);
        (sharedPointer->current_index)++;
        
        sem_post(&(sharedPointer->mutex));
        sem_post(&(sharedPointer->is_filled));
    }
    sharedPointer->flag1 = 1;
}

void* consumer(){
    for(int i = 0; i < M; i++){
        //when producer ends producing and buffer is empty, consumer can stop
        if((sharedPointer->flag1) && ((sharedPointer->current_index) <= 1)) break;
        
        sem_wait(&(sharedPointer->is_filled));
        sem_wait(&(sharedPointer->is_filled));
        sem_wait(&(sharedPointer->mutex));

        printf("Consumed %d and %d\n", sharedPointer->buffer[(sharedPointer->current_index)-1], sharedPointer->buffer[(sharedPointer->current_index)-2]);
        (sharedPointer->current_index) -= 2;

        sem_post(&(sharedPointer->mutex));
        sem_post(&(sharedPointer->space_left));
        sem_post(&(sharedPointer->space_left));
    }
}


int main(){
    //made shred memory for struct shred varibales
    int shmid = shmget(1234, sizeof(struct Shared_variables), IPC_CREAT | 0777);

    //this is the pointer to the shared memory
    sharedPointer = (struct Shared_variables*)shmat(shmid, (void*)0, 0);
    
    //initialising the semaphores
    sem_init(&(sharedPointer->is_filled), 1, 0);
    sem_init(&(sharedPointer->space_left), 1, 5);
    sem_init(&(sharedPointer->mutex), 1, 1);

    sharedPointer->current_index = 0;
    sharedPointer->flag1 = 0;

    //forking to make two independent process
    int rc = fork();
    if(rc < 0){
        printf("Fork Failed\n");
        exit(1);
    } 
    
    else if (0 == rc) consumer(); 
    
    else {
        producer();
        wait(NULL);
    }

    //Destroying the three semaphoress
    sem_destroy(&(sharedPointer->space_left));
    sem_destroy(&(sharedPointer->is_filled));
    sem_destroy(&(sharedPointer->mutex));

    if(sharedPointer->current_index==1) printf("Buffer has one object left = %d\n", sharedPointer->buffer[sharedPointer->current_index-1]);

    return 0;
}