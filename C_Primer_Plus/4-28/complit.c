/* complit.c -- 复合字面量*/
#include <stdio.h>
#include <string.h>
#define MAXAUTL 31	
#define MAXTITL 41


struct book {			// 结构模板：标记是　book
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};

int main()
{
	struct book readfirst;
	int score;


	printf("Enter test score:");
	scanf("%d",&score);

	if(score >= 84)
		readfirst = (struct book){	
						"Crime and Punishment",
						"Jhon Rainbow",
						11.25};
	else	
		readfirst = (struct book){
						"Mr.Bouncy's Nice Hat",
						"Fyed Winsome",
						5.95};

	printf("Your assigned reading:\n");
	printf("%s by %s:$%.2f\n",readfirst.title,readfirst.author,readfirst.value);

	return 0;
}	
