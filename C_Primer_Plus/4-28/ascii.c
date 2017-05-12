/*  输出ASCII字符 */
#include <stdio.h>
int main()
{
	for(int i = 1;i < 128;i++){
	if(i % 8){
		printf("i = %c\t",i);
		}else{
		printf("i = %c\n",i);
		}
	}	
	return 0;
}
