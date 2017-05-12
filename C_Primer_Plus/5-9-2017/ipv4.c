#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define get_str_ip(dst_str,src_uint32) \
    sprintf(dst_str,"%d.%d.%d.%d",(src_uint32>>24)&0xff,(src_uint32>>16)&0xff,(src_uint32>>8)&0xff,src_uint32&0xff)

int InvertIp(unsigned long NormalIp)
{
  unsigned char b1,b2,b3,b4;

  b1 = NormalIp & 0x00FF;
  b2 = (NormalIp >> 8) & 0x00FF;
  b3 = (NormalIp >> 16) & 0x00FF;
  b4 = (NormalIp >> 24) & 0x00FF;

  return (b1 <<24) | (b2 << 16) | (b3 << 8) | b4;
}

int main()
{
	int FirstIp = inet_addr("192.168.0.1");   //任意的开始地址
  	int SecondIp = inet_addr("192.168.0.20"); //任意的结束地址

	 FirstIp = InvertIp(FirstIp);
	 SecondIp = InvertIp(SecondIp);

	int delta = SecondIp - FirstIp;

	char str_ip[18] = {0};
	int temp_ip = 0;
	int i = 0;
	for(; i <= delta;i++){
		get_str_ip(str_ip,FirstIp);
		printf("str_ip = %s\n",str_ip);

        ++FirstIp;
	}
	return 0;
}
