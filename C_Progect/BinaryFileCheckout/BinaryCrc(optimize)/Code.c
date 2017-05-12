#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "F_CRC32.h"
#include "F_SIZE.h"

#define COMPANY_SIGN 15
#define VERSION_SIGN 3
#define STRUCT_SIZE 26
#define MAIN_VERSION 2
#define MIN_VERSION 0
#define RELEASE_VERSION 17

#pragma pack(1)
struct file_header{
	char special[COMPANY_SIGN];
	int version[VERSION_SIGN];
	int CRC;
};

typedef char byte;
int main()
{	//声明变量
	char fname_source[12];

	//获得源文件名
		printf("请输入文件名：");
		scanf("%s",fname_source);

	//打开源文件
	FILE *fsource=fopen(fname_source,"r");
	if(fsource==NULL){
		printf("文件不存在！\n");	
		exit(0);	
		};

	//获得源文件大小
	int fsize_source=F_SIZE(fname_source);
		printf("源文件大小为%d字节\n",fsize_source);

	//计算源文件CRC32
	unsigned int s_crc=F_CRC32(fname_source);
		printf("源文件CRC32值：%x\n",s_crc);

	//打开目标文件
	FILE *fdest=fopen("modify.b","w");

	//填充文件头结构
	struct file_header f_header;
	strcpy(f_header.special,"TKSENSOR.bin");
	f_header.version[0]=MAIN_VERSION;
	f_header.version[1]=MIN_VERSION;
	f_header.version[2]=RELEASE_VERSION;
	f_header.CRC=s_crc;

	//写文件头
	fwrite(&f_header,sizeof(f_header),1,fdest);

	//拷贝剩余
	byte *src_buffer = (byte*)malloc(fsize_source);
	fread(src_buffer,1,fsize_source,fsource);
	fwrite(src_buffer,1,fsize_source,fdest);

	fclose(fsource);
	fclose(fdest);
	return 0;
}
