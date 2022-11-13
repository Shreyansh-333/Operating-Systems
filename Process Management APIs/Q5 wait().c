#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("It's child process\n");
    }
    else{
        printf("It's parent process\n");
        wait(NULL); //waiting for child process to run
        printf("Parent again after execution of child.\n");
    }
    return 0;
}