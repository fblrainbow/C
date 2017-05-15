#include <stdio.h>
#include <string.h>
int main()
{
		int i;
		printf("Please input an int:");
		while(!scanf("%d",&i)){
				while(getchar() != '\n')
						continue;
				printf("You input data is not int,please try input again:");
		}
		printf("You input number is %d\n",i);
		return 0;
}


