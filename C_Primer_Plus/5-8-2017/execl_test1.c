/* execl_test1.c */
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
	execl("cmdline_system","cmdline_system","ls",NULL);
	printf("Error Reading//Executing The File newprog.exe\n");

	return 0;
}
