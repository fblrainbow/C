/* wait_test.c */
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
	pid_t pid;
	int status;
	pid = fork();
	pid = wait(&status);

	if(pid > 0)
		printf("pid %d status %d\n",pid,WEXITSTATUS(status));

	return 0;
}
