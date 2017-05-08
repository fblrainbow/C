#include <stdio.h>
int main()
{
	int i = 0;
	int flag = 0;
	printf("Enter an int number:");

	while(1){
		flag = scanf("%d",&i);
		while(getchar() != '\n')
			continue;
		if(flag)
			break;
		else
			printf(	"Please try again!\n"
					"Enter an int number:");
	}
	printf("You input number is: %d\n",i);
}
