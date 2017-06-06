#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc,char* argv[])
{
		int ch;

		struct option long_options[] ={
				{ "config",1,NULL,0},
				{ "file",1,NULL,0},
				{ "usage",2,NULL,0},
				{ 0,0,0,0}
		};

		int option_index =0;
		while((ch = getopt_long(argc,argv,"abcde",long_options,&option_index)) != -1)
		{
				switch(ch){
						case 'a':
								printf("%c\n",ch);
								break;

						case 'b':
								printf("%c\n",ch);
								break;

						case 'c':
								printf("%c\n",ch);
								break;

						case 'd':
								printf("%c,%s\n",ch,optarg);
								break;

						case 'e':
								printf("%c\n",ch);
								break;
						case 0:
								printf("%s,%s\n",long_options[option_index].name,optarg);
								break;
				}

		}
		return 0;
}
