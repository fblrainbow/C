#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void when_exit()
{
	printf("success to quit!\n");
}
void abort_handler(int i)
{

	printf("%d\n",i);

}
int main(void)
{
	printf("The max number byte of host name is %d\n",_SC_HOST_NAME_MAX);
	atexit(when_exit);
	signal(SIGINT,abort_handler);
	for(int i = 0 ;i < 5;i++ ){
		printf("%d\n",i);
		sleep(1);
	}	
	return 0;
}
