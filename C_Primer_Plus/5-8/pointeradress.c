#include <stdio.h>
#include <string.h>
int main()
{
	char string[] = "I love meilin!";
	char* str = string;
	for(int i = 0;*str;i++)
		printf("str[%d] = %c\t&str[%d] = %p\tstring[%#x] = %c\t *str++ = %c\t&str = %p\t&i = %p\t&(*str++) = %p\t&str[%d] = %p\n",i,str[i],i,&str[i],i,string[i],*str++,&str,&i,&(*str),i,&str[i]);

	return 0;
}
