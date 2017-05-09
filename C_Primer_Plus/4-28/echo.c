/* echo.  is buffer*/
/*#include <stdio.h>
int main(void)

{
	char ch;	
	
	while((ch = getchar()) != '#')
		putchar(ch);
	return 0;
}*/
#include <stdio.h>
int main(void)

{
	char ch;	
	
	while((ch = getchar()) != EOF)
		putchar(ch);
	return 0;
}
