#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 

int main(){
    int x=100;
    int rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("It's child process, Value of x: %d\n", x);
        x=x+100;
        printf("Value of x after changing: %d\n", x);
    }
    else{
        printf("It's parent process, Value of x: %d\n", x);
        x=x+200;
        printf("Value of x after changing is: %d\n", x);
    }
    return 0;
}
