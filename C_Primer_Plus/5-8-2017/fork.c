/* fork.c */
#include <unistd.h>
#include <stdio.h>
int main()

{
	pid_t pid;
	while(1){
		pid = fork();
		if(pid < 0)
			printf("Error Creating New Process!\n");
		else if(0 == pid)
			printf("Child ID Is %d\n",getpid());
		else
			printf("Parent ID Is %d and Child ID Is %d\n",getpid(),pid);
		sleep(5);
	} 
}
