#include <stdio.h>  
#include<unistd.h>  

int main(int argc, char *argv[])  
{  
	int ch;  
	opterr = 0;//不打印错误信息  

	while((ch = getopt(argc,argv,"hv:ck:q:"))!= EOF)  
	{  
		switch(ch)  
		{  
			//第一个参数t后面不跟参数  
			case 'h': printf("--help\n");continue;  

				  //第二个参数l后面要跟参数执行命令并打印参数  
			case 'v': printf("--version: %s\n",optarg); continue;  

			case 'c': printf("Code\n"); continue;  
			case 'k': printf("kill %s\n", optarg); continue;  

				  //第五个参数q后面可跟可不跟参数,一个参数的话必须紧跟q后面不能有空格   
			case 'q': printf("love quite: %s\n",optarg); continue;  

			default: printf("other option :%c\n",ch);  
		}  

	}  
	return 0;  
}  
