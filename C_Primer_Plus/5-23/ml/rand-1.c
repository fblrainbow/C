
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct dataitem{
		float time_during;
		int first_int;
		int second_int;
		int third_int;
		int fourth_int;
		int flag;
}DATA;
DATA function(char*);
int main()
{
		FILE* fp = NULL;
		char* name = "bot200-1.csv";
		fp = fopen(name,"w+");
		if(!fp)
		{
				printf("error!");
				exit(-1);
		}
		srand(time(NULL));
		DATA item;
		float time_during;
		int first_int;
		int second_int;
		int third_int;
		int fourth_int;
		int flag;
		char* string;
		for(int i = 0;i < 5;i++)  
		{
			item.time_during = (rand()%7000)/1000.000+34.678;
			item.first_int = rand()%13+26;
			item.second_int = rand()%14+26;
			item.third_int = rand()%1774+1995;
			item.fourth_int = rand()%1980+11177;
			item.flag = rand()%2+1;
			sprintf(string,"%2.3f,%2d,%2d,%4d,%5d,%1d\n",item.time_during,item.first_int,item.second_int,item.third_int,item.fourth_int,item.flag);
printf("%s",string);
		}

		fclose(fp);
		return 0;
}













