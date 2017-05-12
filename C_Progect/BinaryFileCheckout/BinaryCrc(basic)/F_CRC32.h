uint32_t crc32_table[256];    
int make_crc32_table()  
{  
    uint32_t c;  
    int i = 0;  
    int bit = 0;      
    for(i = 0; i < 256; i++)  
    {  
        c  = (uint32_t)i;          
        for(bit = 0; bit < 8; bit++)  
        {  
            if(c&1)  
            {  
                c = (c >> 1)^(0xEDB88320);  
            }  
            else  
            {  
                c =  c >> 1;  
            }  
              
        }  
        crc32_table[i] = c;  
    }   
}   
uint32_t make_crc(uint32_t crc, unsigned char *string, uint32_t size)  
{   
    while(size--)  
        crc = (crc >> 8)^(crc32_table[(crc ^ *string++)&0xff]);   
    return crc;  
}
int F_CRC32(char filename[]){
int i;  
    FILE *sp = NULL;   
    uint32_t count;  
    uint32_t crc = 0xFFFFFFFF;  
    unsigned char buf[1024];  
    make_crc32_table(); 
    sp = fopen(filename, "rb");  
    if(sp == NULL)  
    {  
        printf("open file error\n");  
        return -1;  
    }   
    if(sp)  
    {  
        while(!feof(sp))  
        {  
            memset(buf, 0, sizeof(buf));  
            count = fread(buf, 1, sizeof(buf), sp);  
            crc = make_crc(crc, buf, count);          
        }  
    }  
    return crc;  
};
