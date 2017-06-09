////////***程序内容：俄罗斯方块********/////////////
/*
   程序共有三个文件main.c tony_tetris.c tony_tetris.h 
   一个编译文件Makefile
*/
///////////////////////////////

#include<stdio.h>
#include"tony_tetris.h"

int main(void )
{
	int ret;
	ret=init();
	if(ret == -1)
	{
		printf("init error!\n");
			return 0;
	}
	while(1)
	{
		ret=control();
		if(ret == -1)
			break;
		
	}
	quit();
	return 0;
}	

