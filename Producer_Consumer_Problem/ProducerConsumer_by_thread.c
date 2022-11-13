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

#define N 10    //for size of buffer
int buffer[N];      //the place where producer inserts and consumer picks.
int Current_index = 0;      //Stores the last index having an object in buffer

#define M 99     //for number of iterations in producers and consumers
pthread_mutex_t mutex_lock;      //mutex lock
sem_t space_left;   //Semaphore to check if there is empty space in buffer
sem_t is_filled;    //Semaphores to check if there is atleast one element in buffer
int flag1 = 0;      //To track if producer has stopped producing when its iterations are done

void* producer(){

    for(int i = 0; i < M; i++){

        sem_wait(&space_left);

        pthread_mutex_lock(&mutex_lock);

        // producer producing a random variable and inserting it in buffer
        int object=rand()%100;
        buffer[Current_index] = object; 
        printf("Produced %d \n", object);
        Current_index+=1;

        pthread_mutex_unlock(&mutex_lock);

        sem_post(&is_filled);
    }
    flag1 = 1;  //When producer is done producing, consumer has to be notified to not wait for producer to insert objects.
}

void* consumer(){
    for(int i = 0; i < M; i++){

        //if producer is finished producing and buffer have less than two objects, consumer has to stop consuming.
        if(flag1 && (Current_index <= 1)) break;

        //As consumer picks two objects at once, two semaphores are required 
        sem_wait(&is_filled);
        sem_wait(&is_filled);

        pthread_mutex_lock(&mutex_lock);

        printf("Consumed %d and %d\n", buffer[Current_index-1], buffer[Current_index-2]);
        Current_index -= 2;

        pthread_mutex_unlock(&mutex_lock);

        sem_post(&space_left);
        sem_post(&space_left);
    }
}

int main(){

    //intialising semaphores and mutex lock
    sem_init(&is_filled, 0, 0);
    sem_init(&space_left, 0, N);
    pthread_mutex_init(&mutex_lock, NULL); 

    //declaring, creating and joining two threads for producer and consumers
    pthread_t t_producer, t_consumer; 
    
    int tid_producer=pthread_create(&t_producer, NULL, &producer, NULL);
    if( tid_producer!= 0) {
        perror("Failed to create producer thread");
    }

    int tid_consumer=pthread_create(&t_consumer, NULL, &consumer, NULL);
    if( tid_consumer!= 0) {
        perror("Failed to create consumer thread");
    }

    pthread_join(t_producer, NULL);
    pthread_join(t_consumer, NULL);

    // Destroying of produced semaphores and mutex locks
    pthread_mutex_destroy(&mutex_lock);
    sem_destroy(&is_filled);
    sem_destroy(&space_left);
    
    if(Current_index==1) printf("Buffer has one object left = %d\n", buffer[Current_index-1]);

    return 0;
}