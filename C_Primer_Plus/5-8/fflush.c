#include <stdio.h>
#include <string.h>

#include <unistd.h>
int main()
{
	int i;
	char s[20];
	int error = scanf("%d,%s",&i,s);	
	while(2 != error){
	fflush(stdin);
	fflush(stdout);
	printf("输入参数非法，请重新输入：");
	printf("%d,%ld\n",error,sizeof(s));
	error = scanf("%d,%s",&i,s); 
	sleep(1);
	}

	printf("学号：%-5d姓名：%-10s\n",i,s);

	return 0;
}
