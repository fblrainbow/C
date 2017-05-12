int F_SIZE(char file_name[]){
	FILE *pFile;
	long size;
	pFile=fopen(file_name,"rb");

	if(pFile==NULL){
		printf("打开文件错误！");
	}else{
		fseek(pFile,0,SEEK_END);
		size=ftell(pFile);
	}

	fclose(pFile);
	return size;
	};
