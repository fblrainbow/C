/* 学生管理系统 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"

/*********************************************main函数*********************************************/
int main(void)
{
	char Num[15] = {'\0'};
	char Name[12] = {'\0'};
	char Sex[5] = {'\0'};
	int Score = -1;

	int select = -1;		//
	DisplayCommand();	
	int STUflag = 1;
	while(STUflag){

		printf("请输入指令:");	
		scanf("%d",&select);
	
		switch(select){
			case 0: 	//0.退出指令	
				STUflag = 0;
				break;
			case 1:		//1.增加一个学生信息
				printf("学号:");
				scanf("%s",Num);
				printf("姓名:");
				scanf("%s",Name);
				printf("性别:");
				scanf("%s",Sex);
				printf("分数:");
				scanf("%d",&Score);
				AddStuMessage(Num,Name,Sex,Score);
				break;

			case 2:		//2.查找指定学生信息
				printf("请输入学号:");
				scanf("%s",Num);
				SearchStuMessage(Num);
				break;

			case 3:		//3.修改指定学生信息
				printf("请输入学号:");
				scanf("%s",Num);
				ModifyStuMessage(Num);
				break;

			case 4:		//4.保存学生信息到文件中
				SaveStuMessage();
					break;

			case 5:		//5.读取文件中的学生信息
				ReadFileStuMessage();
					break;

			case 6:		//6.删除指定学生信息
				printf("请输入学号:");
				scanf("%s",Num);
				DeleteStuMessage(Num);
					break;

			case 7:		//7.恢复删除的学生信息
				printf("请输入学号:");
				scanf("%s",Num);
				ReadFileStuMessage(Num);
					break;

			case 8:		//8.删除保存学生信息的文件
				DeleteFile();
					break;

			case 9:	//9.打印所有学生信息
				PrintStuMessage();
					break;

			case 10://10打印指令信息
				DisplayCommand();
					break;

			case 11://11把文件加载进链表
				LoadStuMessage();
					break;
			default:
				printf("输入的指令错误!\n");
		}
     }
	ClearLinkList();
	return 0;
}
