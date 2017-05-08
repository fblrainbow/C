#include <stdio.h>
#include <stdlib.h>
typedef struct _STU
{
	char StuNum[15];
	char StuName[12];
	char StuSex[5];
	int StuScore;
	struct _STU *pNext;
}STUNODE;
//声明链表的头和尾
STUNODE* g_pHead = NULL;
STUNODE* g_pEnd = NULL;

/*********************************************功能实现*********************************************/

//1.增加一个学生信息
void AddStuMessage(char* StuNum,char* StuName,char* StuSex,int StuScore)	
{	
	if(NULL == StuNum ||NULL == StuName || NULL == StuSex || StuScore < 0 )	//检验参数的合法性
	{
		printf("录入学生信息错误，请再仔细检查之后再输入！\n");
		return ;	
	}

	//逻辑
	STUNODE* p_Temp = malloc(sizeof(STUNODE));	//创建一个节点,赋值

	strcpy(p_Temp->StuNum,StuNum);
	strcpy(p_Temp->StuName,StuName);
	strcpy(p_Temp->StuSex,StuSex);
	p_Temp->StuScore = StuScore;
	p_Temp->pNext = NULL;
	
	if(NULL == g_pHead)		//
	{
		g_pHead = p_Temp;
		g_pEnd = p_Temp;
	}else
	{
		g_pEnd->pNext = p_Temp;

	}
	printf("g_pHead->pNext = %p\n",g_pHead->pNext);	
	printf("成功增加学生信息！\n");
}

//2.查找指定学生信息
void SearchStuMessage(char Num[15])
{	
	STUNODE* p_Temp = g_pHead;
	int count = 0;

	while(p_Temp){
		if(!strcmp(p_Temp->StuNum,Num)){	
			printf("学号:%-15s姓名:%-12s性别:%-10s分数:%5d\n",p_Temp->StuNum,p_Temp->StuName,p_Temp->StuSex,p_Temp->StuScore);
			count++;
			}
			p_Temp = p_Temp->pNext;	
	}	
	
	if(!count)
		printf("找不到你要找的学生信息，请再检查下输入的学号是否正确！\n");
}

//3.修改指定学生信息
void ModifyStuMessage(char Num[])
{
	STUNODE* p_Temp = g_pHead;
	int count = 0;

	while(p_Temp){
		if(!strcmp(p_Temp->StuNum,Num))
				printf("学号:");
				while(1 != scanf("%s",p_Temp->StuNum));
				
				printf("姓名:");
				while(1 != scanf("%s",p_Temp->StuName));
				
				printf("性别:");
				while(1 != scanf("%s",p_Temp->StuSex));
				
				printf("分数:");
				while(1 != scanf("%d",&p_Temp->StuScore));
				
				count++;
				p_Temp = p_Temp->pNext;
	}
	if(!count){
		printf("你要修改的学生不存在,请再检查下你要修改的学号！\n");
	}
}

//4.保存学生信息到文件中
void SaveStuMessage()
{
	STUNODE* p_Temp = g_pHead;
	FILE *fp = NULL;

	fp = fopen("StuMessageRecord.db","a+");
	if(!fp){
		printf("打开文件失败!\n");
			exit(0);	
			 }

	char buffer[50];
	int count = 0;

	while(p_Temp){

		sprintf(buffer,"%s %s %s %d\n",p_Temp->StuNum,p_Temp->StuName,p_Temp->StuSex,p_Temp->StuScore);
		fputs(buffer,fp);
		printf("%s",buffer);
		p_Temp = p_Temp->pNext;
		count++;
	}
	
	if(count)
		printf("成功保存学生信息文件!\n");
	else 
		printf("没有要保存的学生信息!\n");
	fclose(fp);
}

//5.读取文件的学生信息
void ReadFileStuMessage()
{
		FILE* fp = NULL;
		char buffer[50],string[15];

		if((fp = fopen("StuMessageRecord.db","r")) == NULL){
			printf("Open file failure!\n");
			exit(-1);	
		}
	
		int idcount = 0;

			STUNODE* p_Temp = NULL;

    	while(fgets(buffer,50,fp) != NULL){
			idcount++;
			memset(string,'\0',15);
			for(int i = 0,j = 0,count = 0;;i++,j++){
				if(0 ==count) {
						if(buffer[i] != ' '){ 
							string[j] = buffer[i];
							}else{
								count++;
								printf("学号:%-15s",string);
								i++;
								j = 0;
							memset(string,'\0',15);
							}
				}

				if(1 == count){
						if(buffer[i] != ' '){
							 string[j] = buffer[i];
							}else{
								count++;
								printf("姓名:%-12s",string);
								j = 0;
								i++;
							memset(string,'\0',15);
							}
				}

				if(2 == count){ 
						if(buffer[i] != ' '){
							string[j] = buffer[i];
							}else{
								count++;
								printf("性别:%-10s",string);
								i++;
								j = 0;
							memset(string,'\0',15);
							}
				}

				if(3 == count){
						if(buffer[i] != '\n'){
							string[j] = buffer[i];
							}else{
								printf("分数:%-5s\n",string);
							memset(string,'\0',15);
							
				break;
							}
				}
			}
		}

		if(!idcount)
			printf("学生信息为空!\n");
		fclose(fp);
}

//6.删除指定学生信息
void DeleteStuMessage(char Num[])
{
	STUNODE* p_Temp = g_pHead;
	int count = 0;

	if(!p_Temp)
			printf("rm NULL!\n");
		else if(!p_Temp->pNext){
			if(!strcmp(p_Temp->StuNum,Num)){
				p_Temp = g_pHead = NULL;		
				count++;
				free(p_Temp);
			}
		}
	else{ 
		while(p_Temp->pNext){
			if(!strcmp(p_Temp->pNext->StuNum,Num)){
				p_Temp->pNext =p_Temp->pNext->pNext;
				count++;
				}
				p_Temp = p_Temp->pNext;
			}

	}	

	if(count)
		printf("成功删除指定学生信息!\n");
	else
		printf("你所要删除的学生信息不存在，请核对后再操作！\n");	

}

//7.恢复删除的学生信息
void RecorveryDeleStuMessage(char Num[])
{

}
//8.删除保存学生信息的文件
void DeleteFile()
{
	system("rm -rf StuMessageRecord.db");
	FILE* fp = fopen("StuMessageRecord.db","r");
		if(!fp)
			printf("成功删除学生信息文件\n");

}

//9.打印所有学生信息
void PrintStuMessage()	
{
	STUNODE* p_Temp = g_pHead;
	int count = 0;
	while(p_Temp)
	{
		printf("g_pHead = %p\tg_pHead = %p\n",g_pHead,g_pHead->pNext);
		printf("p_Temp = %p\tp_Temp->pNext = %p\n",p_Temp,p_Temp->pNext);
		printf("学号:%-15s姓名:%-12s性别:%-10s分数:%-6d\n",p_Temp->StuNum,p_Temp->StuName,p_Temp->StuSex,p_Temp->StuScore);
		count++;
		p_Temp = p_Temp->pNext;
	}
	
	if(count)
		printf("成功打印%d个学生信息！\n",count);
	else
		printf("学生信息个数为零！\n");
}

//10.打印指令信息
void DisplayCommand()	
{
	printf("******************************学生管理系统******************************\n"
	       "*****************************本系统指令如下*****************************\n"
	       "********		 1.增加一个学生信息                     ********\n"
	       "********		 2.查找指定学生信息(姓名/学号)          ********\n"
	       "********		 3.修改指定学生信息                     ********\n"
	       "********		 4.保存学生信息到文件中                 ********\n"
	       "********		 5.读取文件中的学生信息                 ********\n"
	       "********		 6.删除指定学生信息                     ********\n"
	       "********		 7.恢复删除的学生信息                   ********\n"
	       "********		 8.删除保存学生信息的文件               ********\n"
	       "********		 9.打印所有学生信息                     ********\n"
	       "********		 10.打印指令列表                        ********\n"
	       "********		 11.把文件加载进链表                    ********\n"
	       "********		 0.退出系统 	                        ********\n"
           "******************************学生管理系统******************************\n");
}

//11.把文件加载进链表
void LoadStuMessage()
{
		FILE* fp = NULL;
		if((fp = fopen("StuMessageRecord.db","r")) == NULL){
			printf("Open file failure!\n");
			exit(-1);	
		}
		char buffer[50],string[15];
		int score = -1;
		int idcount = 0;
			
    while(fgets(buffer,50,fp) != NULL){
		STUNODE* p_Temp = malloc(sizeof(STUNODE));
			idcount++;
			printf("%s",buffer);
			memset(string,'\0',15);
			for(int i = 0,j = 0,count = 0;;i++,j++){
				if(0 ==count) {
						if(buffer[i] != ' '){ 
							string[j] = buffer[i];
							}else{
								count++;
								printf("学号:%-15s",string);
								strcpy(p_Temp->StuNum,string);
								j = 0;
								i++;
							memset(string,'\0',15);
							}
				}

				if(1 == count){
						if(buffer[i] != ' '){
							 string[j] = buffer[i];
							}else{
								count++;
								printf("姓名:%-12s",string);
								strcpy(p_Temp->StuName,string);
								j = 0;
								i++;
							memset(string,'\0',15);
							}
				}

				if(2 == count){ 
						if(buffer[i] != ' '){
							string[j] = buffer[i];
							}else{
								count++;
								printf("性别:%-10s",string);
								strcpy(p_Temp->StuSex,string);
								i++;
								j = 0;
							memset(string,'\0',15);
							}
				}

				if(3 == count){
						if(buffer[i] != '\n'){
							string[j] = buffer[i];
							}else{
								printf("分数:%-5s\n",string);
								 score = atoi(string);
								p_Temp->StuScore = score;
								p_Temp->pNext = NULL;

							memset(string,'\0',15);

				if(!g_pHead){
						g_pHead = p_Temp;
						g_pEnd = p_Temp;
				}else{
						g_pEnd = p_Temp;	
						printf("p_Temp = %p\n",p_Temp);
				}

				break;
							}
				}
			}
	}
			printf("g_pHead = %p\n",g_pHead);
		if(!idcount)
			printf("加载学生信息为空！\n");
		else
			printf("加载%d个学生信息！\n",idcount);
		fclose(fp);
}



//清空链表
void ClearLinkList()
{
	STUNODE* p_Temp = g_pHead;
	int count = 0;

	while(g_pHead != NULL){
	 	p_Temp = g_pHead;
		g_pHead = g_pHead->pNext;
		free(p_Temp);	
		printf("释放链表结点：%d\n",++count);	
	}
		
	if(count)
		printf("释放链表完毕！\n");
	else
		printf("链表结点个数为零！\n");
}

//2017年 04月 26日 星期三 03:31:09 CST


//846058904@qq.com!
//2017年 04月 14日 星期五 00:53:24 CST
