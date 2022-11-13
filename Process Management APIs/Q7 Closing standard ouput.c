#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
 

int main(){
    int rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("It's child process before closing standard output\n");
        close(STDOUT_FILENO); 
        printf("This shouldn't print\n");
    }
    else{
        printf("It's parent process\n");
    }
    return 0;
}