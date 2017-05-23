#include <string.h>
#include <stdio.h>
int main()
{
	char str1[10];
	char* str2 ="asfaf";
	
	strcpy(str1,str2);
	printf("%s\n",str1);
}
