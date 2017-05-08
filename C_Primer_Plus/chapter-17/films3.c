/* films3.c  --使用抽象数据类型(ADT)风格的链表　*/
/* 与list.c一起编译								*/
#include <stdio.h>
#include <string.h>
#include "list.h"

void showmovies(Item item);
char* s_gets(char* st,int n);

int main(void)
{
		List movies;
		Item temp;

		/* 初始化 */
		InitializeList(&movies);
		if(ListIsFull(&movies)){
				fprintf(stderr,"No memory available! Bye!\n");
				exit(1);
		}

		/* 获取用户输入并存储 */
		puts("Enter first movie title:");
		while(s_gets(temp.title,TSIZE) != NULL && temp.title[0] != '\0'){
				puts("Enter your rating <0-10>:");
				/*---------------fbl--------while(!scanf("%d",&temp.rating)){
				  while(getchar() != '\n')
				  continue;
				  puts("Please try enter rating again <0-10>:");
				  }*/
				scanf("%d",&temp.rating);
				while(getchar() != '\n'){
						continue;
						puts("Please try enter rating again <0-10>:");
				}

				if(AddItem(temp,&movies) == false){
						fprintf(stderr,"Problem allocating memory\n");
						break;
				}
				if(ListIsFull(&movies)){
						puts("The list is now full.\n");
						break;
				}
				puts("Enter next movie title (empty line to stop):");
				/*---------fbl-----------while(getchar() != '\n')
				  continue;*/

		}

		/* 显示				*/
		if(ListIsEmpty(&movies))
				printf("No data entered.\n");
		else{
				printf("Here is the movie list:\n");
				Traverse(&movies,showmovies);
		}
		printf("You entered %d movies.\n",ListItemCount(&movies));


		/* clear up */
		EmptyTheList(&movies);
		printf("Bye!\n");

		return 0;
}

void showmovies(Item item)
{
		printf("Movie: %s Rating: %d\n",item.title,item.rating);
}

char* s_gets(char* st,int n)
{
		char* ret_val;
		char* find;

		ret_val = fgets(st,n,stdin);
		if(ret_val){
				find = strchr(st,'\n');
				if(find)
						*find = '\0';
				else
						while(getchar() != '\n')
								continue;	
		}

		return ret_val;
}
