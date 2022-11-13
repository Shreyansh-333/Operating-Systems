#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 

int main(){
    pid_t rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("It's child process\n");
    }
    else{
        pid_t wc = waitpid(rc, 0, WUNTRACED);
        printf("It's parent process\n");
    }
    return 0;
}