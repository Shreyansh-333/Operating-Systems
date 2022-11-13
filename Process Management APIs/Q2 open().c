#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
 
// int main(){
//     int fd = open("RefFile.c", O_RDONLY); //fd stand for file discripter

//     if(fd == -1 ){printf("Can't open file\n exiting....\n");}
    
//     int rc = fork();
    
//     if (rc < 0){fprintf(stderr, "fork failed\n");}
    
//     else if (rc == 0){
//         // child process
//         printf("This is child process (pid:%d)\n", (int)getpid());
//         char c;
//         read(fd, &c,1);
//         printf("Taking a character from child process \n%c\n", c);
//     }
    
//     else{
//         //parent process
//         wait(NULL);
//         printf("This is parent %d (pid:%d)\n", rc, (int)getpid());
//         char c;
//         read(fd, &c,1);
//         printf("Taking a character from parent process\n%c\n", c);
//     }
//     return 0;
// }

int main(){
    int file_des = open("q2a_2_file_des", O_RDONLY);
    int rc= fork();
    if(rc<0) {
        printf("Fork failure\n");
    }
    else if(rc==0){
        printf("It's child process");
    }
    else{
        printf("It's parent process");
    }
    return 0;
}