#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#define COUNT 4100
int main()
{
		uint32_t time_second = 28600;
		uint8_t day = 1;	
		uint16_t usecond = 0;
		uint8_t second = 0;
		uint8_t minute =0;
		uint8_t hour = 0;

		char str_usecond[3];
		char str_second[3];
		char str_minute[3];
		char str_hour[3];
		srand(time(NULL));

		char string[30];
		FILE* fp = NULL;
		fp = fopen("4-1_time_4100.csv","w+");

		for(int i = 0;i < COUNT;i++)
		{
				time_second += rand()%3+600;
				usecond = rand()%1000;
				hour = time_second/3600;
				hour = hour < 24?hour:(++day,time_second -= 86400,hour-24);
				minute = (time_second - hour*3600)/60;
				second = time_second%60;
				
				if(usecond > 99)
					sprintf(str_usecond,"%u",usecond);
				else if(usecond > 9)
					sprintf(str_usecond,"0%u",usecond);
				else
					sprintf(str_usecond,"00%u",usecond);
			
	
				if(second < 10)
						sprintf(str_second,"0%u",second);
				else
						sprintf(str_second,"%u",second);

				if(minute < 10)
						sprintf(str_minute,"0%u",minute);
				else
						sprintf(str_minute,"%u",minute);

				if(hour < 10)
						sprintf(str_hour,"0%u",hour);
				else
						sprintf(str_hour,"%u",hour);
				if(day < 10)
				sprintf(string,"2017-04-0%u %s:%s:%s.%s,\n",day,str_hour,str_minute,str_second,str_usecond);
				else
				sprintf(string,"2017-04-%u %s:%s:%s.%s,\n",day,str_hour,str_minute,str_second,str_usecond);

				fwrite(string,25,1,fp);
		}

		fclose(fp);
		return 0;
}
