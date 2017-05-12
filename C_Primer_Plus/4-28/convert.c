/* convert.c --自动类型转换  */
#include <stdio.h>
int main()
{
	char ch;
	int i;
	float fl;

	fl = i = ch = 'c';
	printf("ch = %c,i = %d,fl = %2.2f\n",ch,i,fl);

	ch = ch + 1;
	i = fl + 2 * ch;
	fl = 2.0 * ch + i;
	printf("ch = %c,i = %d,fl = %2.2f\n",ch,i,fl);

	ch = 356;
	printf("Now ch = %c\n",ch);
	
	ch = 80.89;
	printf("Now ch = %c\n",ch);
	
	return 0;
}
