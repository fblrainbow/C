/* n! =   */
#include <stdio.h>
int fun(int n){
	return n == 1?1:n*fun(n-1);
}
int main(int argc,char* argv[])
{
	int n;
	printf("Please input N:");
	while(!scanf("%d",&n))
		while(getchar() == '\n')
			continue;
	int sum = fun(n);
	printf("sum = %d\n",sum);
}
