/* continue in switch */
#include <stdio.h>
int main()
{
	int i;
	
	printf("Input i:");
	scanf("%d",&i);

	switch(i){

		case 1: 
			printf("1\n");	break;
		case 2:	
			printf("2\n");	break;
		case 3:	
			printf("3\n");	continue;
		case 4:	
			printf("4\n");	continue;
		case 5:	
			printf("5\n");	continue;
	}
	return 0;
}
