#include <stdio.h>  
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>  
#include <unistd.h>  

int main(int argc, char* argv[])  
{  
	pid_t pid;  

	pid = fork();  
	if(0 == pid)  
	{  
		printf("This is child process, %d\n", getpid());  
		sleep(5);  
	}  
	else  
	{  
		wait(NULL);  
		printf("This is parent process, %d\n", getpid());  
	}  

	return 1;  
}
