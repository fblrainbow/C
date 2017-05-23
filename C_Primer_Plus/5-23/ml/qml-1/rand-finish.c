#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
		FILE* fp = NULL;
		char* name = "bot200-1.csv";
		fp = fopen(name,"a+");
		if(!fp)
		{
				printf("error!");
				exit(-1);
		}
		srand(time(NULL));
		float time_during;
		int first_int;
		int second_int;
		int third_int;
		int fourth_int;
		int flag;
		char string[26];
		for(int i = 0;i < 10000;i++)  
		{
				time_during = (rand()%7000)/1000.000+34.678;
				first_int = rand()%13+26;
				second_int = rand()%14+26;
				third_int = rand()%1774+1995;
				fourth_int = rand()%1980+11177;
				flag = rand()%2+1;
				sprintf(string,"%2.3f,%2d,%2d,%4d,%5d,%1d\n",time_during,first_int,second_int,third_int,fourth_int,flag);
//				printf("%s",string);

				fwrite(string,sizeof(string),1,fp);
		}

		fclose(fp);
		return 0;
}
