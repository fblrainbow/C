#include <stdio.h>

int max(int x,int y)
{
	return x > y? x : y;
}
int main()
{
	int x = 5, y = 8;
	int (*ptr)(int,int);
	ptr = max;
	int c = (*ptr)(x,y);
	printf("%d,%d,%d",x,y,c);

	return 0;
}
