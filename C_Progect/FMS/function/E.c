
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main ()
{
	char account_name[] = "fbl.txt";
	FILE* account_pointer = NULL;
	account_pointer = fopen(account_name,"aw+");
		printf("adress:");
	char adress[33];
		scanf("%s",adress);
	fwrite(adress,1,strlen(adress),account_pointer);
	fwrite("\t",1,1,account_pointer);
		printf("account:");
	char account[33];
		 scanf("%s",account);
	fwrite(account,1,strlen(account),account_pointer);
	fwrite("\t",1,1,account_pointer);
		printf("passwd:");
	char passwd[20];
		scanf("%s",passwd);
	fwrite(passwd,1,strlen(passwd),account_pointer);
	fwrite("\n",1,1,account_pointer);
		printf("添加帐号密码完毕\n");
	fclose(account_pointer);
	return 0;
}
void function_E(char account_name[]){
	printf("\t\t站点\t\t\t帐号\t\t\t密码\t\t\n");	
