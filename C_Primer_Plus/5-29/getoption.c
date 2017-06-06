#include <unistd.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
		int ch;
		while((ch = getopt(argc,argv,"abcd:")) != -1)
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

				}
		}








		return 0;
}
