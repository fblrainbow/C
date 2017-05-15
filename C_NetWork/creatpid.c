#include <stdio.h>  
#include <string.h>
#include <unistd.h>  
#include <stdlib.h>  
#include <math.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
  
int main()  
{  
    pid_t pid;  
  
    if(-1 == (pid = fork()))  
    {  
        printf("Error happened in fork function!\n");  
        return 0;  
    }  
  
    if(0 == pid)  
    {  
        printf("This is child process: %d\n", getpid());  
    }  
    else  
    {  
        printf("This is parent process: %d\n", getpid());  
    }  
  
    return 0;  
}  
