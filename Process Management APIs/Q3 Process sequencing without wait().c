#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(){
    int rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("Hello, It's child process, (parent process running in a second)\n");
    }
    else{
        sleep(1);
        printf("Gooodbye! It's parent process\n");
    }
    return 0;
}