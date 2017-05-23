#include <stdio.h>
#include <string.h>
#include <time.h>
int main(int argc, char **argv)  
{  
    time_t t;  
    t = time(NULL);  
    struct tm *lt;  
    int ii = time(&t);  
    printf("ii = %d\n", ii);  
    t = time(NULL);  
    lt = localtime(&t);  
    char nowtime[24];  
    memset(nowtime, 0, sizeof(nowtime));  
    strftime(nowtime, 24, "%Y-%m-%d %H:%M:%S", lt);  
    printf("nowtime = %s\n", nowtime);  
    return 1;  
}
