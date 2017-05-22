#include <stdio.h>
#include <string.h>
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
		char* name = "bot200.csv";
		fp = fopen(name,"rb+");
		if(!fp)
		{
				printf("error!");
				exit(-1);
		}
		DATA item;
		char string[32];
		double time_during = 0.0;
		float first_int =  0;
		float second_int = 0;
		float third_int = 0;
		float fourth_int = 0;
		float flag = 0;
		int i = 0;
		for(i = 0;i < 901;i++)  
		{
				fgets(string,sizeof string,fp);
				item = function(string);
				time_during += item.time_during;
				first_int += item.first_int;
				second_int += item.second_int;
				third_int += item.third_int;
				fourth_int += item.fourth_int;
				flag += item.flag;
		}

printf("time = %lf,first_int = %f,second_int = %f,third_int = %f,fourth_int = %f,flag = %f\n",time_during/i,first_int/i,second_int/i,third_int/i,fourth_int/i,flag/i);

		fclose(fp);

		return 0;
}
DATA function(char* string)
{				
		DATA Temp;
		char str[10];	
		char* p = strtok(string,",");
		strcpy(str,p);

		int strint = 0,sum = 0;			
		for(int i = 0;i < 6;i++)
		{
				if(str[i] == '.')
						continue;
				strint = str[i]-48;
				sum=sum*10+strint;
		}	
		float time_during = sum/1000.000;
		//printf("%f",time_during);

		p = strtok(NULL,",");
		int first_int = atoi(p);
		//printf("%d\t",first_int);

		p = strtok(NULL,",");
		int second_int = atoi(p);				
		//printf("%d\t",second_int);

		p = strtok(NULL,",");
		int third_int = atoi(p);
		//printf("%d\t",third_int);

		p = strtok(NULL,",");
		int fourth_int = atoi(p);
		//printf("%d\t",fourth_int);

		p = strtok(NULL,",");
		int flag = atoi(p);
		//printf("%d\n",flag);
		
		Temp.time_during =  time_during;
		Temp.first_int = first_int;
		Temp.second_int = second_int;
		Temp.third_int= third_int;
		Temp.fourth_int = fourth_int;
		Temp.flag = flag;
		return Temp;
}

















