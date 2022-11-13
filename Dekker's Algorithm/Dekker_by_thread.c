#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 100000


int shmid, *process_turn, *child_wants_to_enter, *parent_wants_to_enter, *target;
// child_wants_to_enter=process_turn+1;
// parent_wants_to_enter=process_turn+2;
// target=process_turn+3;

void *child(){
    *child_wants_to_enter=1;
    while(*parent_wants_to_enter){
        if(*process_turn==2){
            *child_wants_to_enter=0;
            while(*process_turn==2);
            *child_wants_to_enter=1;
        }
    }
    *target+=1;
    // printf("%d\n",*target);
    *child_wants_to_enter=0;
    *process_turn=2;
}

void *parent(){
    *parent_wants_to_enter=1;
    while(*child_wants_to_enter){
        if(*process_turn==1){
            *parent_wants_to_enter=0;
            while(*process_turn==1);
            *parent_wants_to_enter=1;
        }
    }
    *target+=1;
    // printf("%d\n",*target);
    *parent_wants_to_enter=0;
    *process_turn=1;
}

int main(){
    shmid = shmget(1334, 4*sizeof(int), IPC_CREAT | 0777);
    process_turn = (int*)shmat(shmid, (void*)0, 0);
    child_wants_to_enter=process_turn+1;
    parent_wants_to_enter=process_turn+2;
    target=process_turn+3;
    *process_turn = 1;
    *child_wants_to_enter = 0;
    *parent_wants_to_enter = 0;
    *target = 0;
    printf("Initial Value of shared variable: %d\n",*target);
    pthread_t thread1;
    pthread_t thread2;
    // int rc=fork();
    int n=0;
    for (n=0;n<N;n++){
        pthread_create(&thread1, NULL, &child, NULL);
        pthread_create(&thread2, NULL, &parent, NULL);
        
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        // if(rc==0){
        //     child();
        // }
        // else if(rc>0){
        //     parent();
        //     wait(NULL);
        // }
    }
    
    printf("Final Value of shared variable: %d\n",*target);

    return 0;
}