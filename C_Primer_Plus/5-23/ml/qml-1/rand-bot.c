#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
		FILE* fp = NULL;
		char* name = "bot-4000.csv";
		fp = fopen(name,"w+");
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
		int flag = -1;
		char string[30];
		for(int i = 0;i < 4000;i++)  
		{	
				if(rand()%2)
						flag = 1;
				time_during = flag*(rand()%1411)/1000.000+40.36273;

				if(rand()%2)
						flag = 1;
				else
						flag = -1;
				first_int = flag*rand()%6+30;

				if(rand()%2)
						flag = 1;
				else
						flag = -1;
				second_int = flag*rand()%7+31;

				if(rand()%2)
						flag = 1;
				else
						flag = -1;
				third_int = flag*rand()%401+2720;

				if(rand()%2)
						flag = 1;
				else
						flag = -1;
				fourth_int = flag*rand()%1101+11081;

				sprintf(string,"%2.3f,%2d,%2d,%4d,%5d\n",time_during,first_int,second_int,third_int,fourth_int);
//				printf("%s",string);
				fwrite(string,24,1,fp);
		}

		fclose(fp);
		return 0;
}













