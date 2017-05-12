/* binbit.c --使用位操作显示二进制　*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>  		//提供CHAR_BIT的定义，CHAR_BIT表示每字节的位数
char* itobs(int,char*);
void show_bstr(const char*);

int main(void)
{
	char bin_str[CHAR_BIT * sizeof(int) + 1];
	int number = 0;
	bool flag = true;
	puts("Enter integers and see them in binary.");
	puts("Non-numberic input terminates program.");
	while(flag){

	scanf("%d",&number);
printf("0");
		itobs(number,bin_str);
printf("1");
		printf("%d is ",number);
		show_bstr(bin_str);
printf("2");
		putchar('\n');
	}
	
	puts("Bye!");

	return 0;
}

char* itobs(int n, char* ps)
{
	int i;
	const static int size = CHAR_BIT * sizeof(int);
	
	for(i = size - 1;i >= 0;i--, n >>= 1)
		ps[i] = (1 & n) + '0';
		ps[size] = '\0';
	
		return ps;
}

/* 4位一组显示二进制字符串　*/
void show_bstr(const char* str)
{
	int i;
	
	while(str[i])   /* 不是一个空字符　*/
	{
			putchar(str[i]);
			if(++i % 4 == 0 && str[i])
				putchar(' ');
	}
}

























