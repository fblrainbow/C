#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
		FILE* fp = NULL;
		char* name = "sport-4000.csv";
		fp = fopen(name,"w+");
		if(!fp)
		{
				printf("error!");
				exit(-1);
		}
		srand(time(NULL));
		int fourth_int;
		int flag = -1;
		char string[30];
		for(int i = 0;i < 4000;i++)  
		{	
				if(rand()%2)
						flag = 1;
				else
						flag = -1;
				fourth_int = flag*rand()%501+2810;

				sprintf(string,"%4d,\n",fourth_int);
//				printf("%s",string);
				fwrite(string,6,1,fp);
		}

		fclose(fp);
		return 0;
}













