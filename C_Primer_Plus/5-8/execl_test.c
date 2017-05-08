
/* execl_test.c */
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
	pid_t pid;
	pid = fork();

	if(pid == 0)
		execl("cmdline_system","fflush",NULL);
	printf("Parent process after if statement\n");

	return 0;
}
