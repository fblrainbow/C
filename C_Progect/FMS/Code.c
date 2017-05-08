#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	 printf("---------------------------分隔符--------------------------\n"
	 	"|A.添加帐号\tB.加密文件\tC.关机重启\tD.新建文件|\n"
		"|E.输出帐号\tF.删除文件\tG.关机重启\tH.新建文件|\n"
		"|I.添加帐号\tJ.加密文件\tK.关机重启\tL.新建文件|\n"
		"|M.添加帐号\tN.加密文件\tO.关机重启\tP.新建文件|\n"
		"|Q.添加帐号\tR.加密文件\tS.关机重启\tT.新建文件|\n"
		"|U.添加帐号\tV.加密文件\tW.关机重启\tX.新建文件|\n"
		"|Y.添加帐号\tZ.加密文件\tC.关机重启\tD.新建文件|\n"
		"---------------------------分隔符--------------------------\n"
		"请输入选项：");

	char option;
	option = getchar();
	switch(option){
		case 'A':
			case 'a':system("bash bash/A.sh");break; 
		case 'B':
			case 'b':system("bash bash/B.sh");break;
		case 'C':
			case 'c':system("bash bash/C.sh");break;
		case 'D':
			case 'd':system("bash bash/D.sh");break;
		case 'E':
			case 'e':system("bash bash/E.sh");break;  
		default:		printf("Error!\n");
	}

	return 0;
}
