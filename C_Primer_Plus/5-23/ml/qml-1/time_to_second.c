#include <stdio.h>  
#include <time.h>  
#include <string.h>  
#include <stdlib.h>  

long GetTick(char *str_time)  
{  
		struct tm stm;  
		int iY, iM, iD, iH, iMin, iS;  

		memset(&stm,0,sizeof(stm));  

		iY = atoi(str_time);  
		iM = atoi(str_time+5);  
		iD = atoi(str_time+8);  
		iH = atoi(str_time+11);  
		iMin = atoi(str_time+14);  
		iS = atoi(str_time+17);  

		stm.tm_year=iY-1900;  
		stm.tm_mon=iM-1;  
		stm.tm_mday=iD;  
		stm.tm_hour=iH;  
		stm.tm_min=iMin;  
		stm.tm_sec=iS;  

		/*printf("%d-%0d-%0d %0d:%0d:%0d\n", iY, iM, iD, iH, iMin, iS);*/  

		return mktime(&stm);  
}  

int main()  
{  
		char str_time[19];  

		printf("请输入时间:"); /*(格式:2011-12-31 11:43:07)*/  

		gets(str_time);  

		printf("%ld\n", GetTick(str_time));  

		return 0;      
}  
