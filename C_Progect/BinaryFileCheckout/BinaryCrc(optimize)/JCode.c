#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define COMPANY_SIGN 15
#define VERSION_SIGN 3

#include "F_CRC32.h"
#include "F_SIZE.h"
#pragma pack(1)
typedef struct{
	 	char special[COMPANY_SIGN];
		int version[VERSION_SIGN];
		int CRC;
	}file_header;
 	typedef char byte;
int main()
{	
	//将文件头按结构体形式输出;
	char f_name[]="modify.b";
	FILE *fsource=fopen(f_name,"r");
	file_header f_header;
	if(fsource == NULL){
		printf("文件不存在，即将退出程序！\n");	
		exit(0);	
		};
	printf("正在输出文件头！\n");
	fread(&f_header,1,sizeof(f_header),fsource);

	//还原文件
	int file_size;
	file_size=F_SIZE(f_name)-sizeof(f_header);
	printf("还原文件大小为%d字节！\n",file_size);
	printf("正在输出数据文件!\n");

	char o_name[]="object.b";
	FILE *fobject=fopen(o_name,"w");
	byte *object_buffer=(byte*)malloc(file_size);
	fread(object_buffer,1,file_size,fsource),
	fwrite(object_buffer,1,file_size,fobject);
	fclose(fobject);
	//计算还原文件CRC32值
	unsigned int o_crc;
	o_crc=F_CRC32(o_name);
	printf("还原文件CRC32值：%x\n",o_crc);
	//比较结构体成员CRC值与还原文件CRC值	
	if(f_header.CRC==o_crc){
		printf("文件正确！\n");
	    }else{
		printf("文件错误！\n");
		}
	fclose(fsource);
	return 0;
}
