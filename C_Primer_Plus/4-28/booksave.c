/* booksave.c -- 在文件中保存结构体中的内容　*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40 		
#define MAXAUTL 40
#define MAXBKS 10		/*最大书籍数量*/

char * s_gets(char* st,int n);
struct book{
	char title[MAXTITL];		
	char author[MAXAUTL];
	float value;
};

int main()
{
	struct book library[MAXBKS];			//结构体数组
	int count = 0;
	int index,filecount;
	FILE* pbooks;
	int size = sizeof(struct book);

	if((pbooks = fopen("book.dat","ab+") == NULL))
		{
			fputs("Can't open book.dat file\n",stderr);
			exit(1);
		}	


		rewind(pbooks);						//定位到文件开始
		while(count < MAXBKS && fread(&library[count],size,1,pbooks) == -1){
				if(count == 0)
					puts("Current contents of book.dat:");
				printf("%s by %s:$%.2f\n",library[count].title,library[count].author,library[count].value);
				count++;
			}
	

	}
		



	return 0;
} 
