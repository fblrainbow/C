#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#define INCRESS	20
int main(int argc,char* argv[])
{
		char ch;
		char str_head[11];
		int transform = 0;

		FILE* fileread = NULL;
		FILE* filewrite = NULL;

		fileread = fopen(argv[2],"r+");
		filewrite = fopen(argv[3],"a+");

		if(0 == strcmp("encryption",argv[1]))
		{
				printf("Encryption %s.\n",argv[2]);
				goto Encryption;
		}
		else if(0 == strcmp("decode",argv[1]))
		{
				printf("Decode %s.\n",argv[2]);
				goto Decode;
		}
		else
		{

				printf("Usage error!\n");

				goto end;
		}


Encryption:
		fwrite("Encryption",sizeof("Encryption"),1,filewrite);
		while(!feof(fileread))
		{	
				fread(&ch,1,1,fileread);
				transform = (int)ch + INCRESS;
				fwrite(&transform,1,1,filewrite);
		}
		printf("Encryption compeleted!\n");
		goto end;

Decode:
		//memset(str_head,'\0',sizeof("encryption"));

		fread(str_head,sizeof("encryption"),1,fileread);
		if(0 == strcmp("Encryption",str_head))
		{	
				while(!feof(fileread))
				{
						fread(&ch,1,1,fileread);
						transform = (int)ch - INCRESS;
						fwrite(&transform,1,1,filewrite);			
				}
		}
		else
		{
				printf("The file hasn't encryption.\n");
		}

		printf("Decode compeleted!\n");
		goto end;
end:
		fclose(fileread);
		fclose(filewrite);

		return 0;
}
