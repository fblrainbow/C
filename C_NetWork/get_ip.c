#include <stdio.h>  
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/ioctl.h>  
#include <netinet/in.h>  
#include <net/if.h>  
#include <net/if_arp.h>  
#include <arpa/inet.h>  
#include <errno.h>  

#define ETH_NAME        "enp0s31f6"  

int main()  
{  
	int sock;  
	struct sockaddr_in sin;  
	struct ifreq ifr;  

	sock = socket(AF_INET, SOCK_DGRAM, 0);  
	if (sock == -1)  
	{  
		perror("socket");  
		return -1;                  
	}  

	strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);  
	ifr.ifr_name[IFNAMSIZ - 1] = 0;  

	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)  
	{  
		perror("ioctl");  
		return -1;  
	}  

	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));  
	fprintf(stdout, "eth0: %s\n", inet_ntoa(sin.sin_addr));  

	return 0;  
}
