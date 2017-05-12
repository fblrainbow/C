/* scanf二仪性 */
#include <stdio.h>
int main(void)
{
	int i = 0,sum = 0;
	while(1 == scanf("%d",&i))
		sum += i;
	printf("%d\n",sum);
	return 0;
}
