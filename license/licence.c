#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "TL_MD5.h"  


int main(int argc, char *argv[])  
{  
	FILE *fp;
	MD5_CTX md5;  
	MD5Init(&md5);           
	int i;  
//	unsigned char encrypt[] = "admin";//21232f297a57a5a743894a0e4a801fc3  
	unsigned char decrypt[16];      

	system("/home/mytest/license/hw-get.sh");

	fp = fopen("/home/hw.tmp", "r+");
	if(NULL == fp)
	{
		printf("cannot open the file !!!");
		return 1;
	}
	fseek(fp, -1, SEEK_END);
	fwrite("ancunkeji", sizeof("ancunkeji"), 1, fp);
	int file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* encrypt = (char*)malloc(file_size * sizeof(char)); 
	fread(encrypt, file_size, sizeof(char), fp);
	fclose(fp);

	MD5Update(&md5,encrypt,strlen((char *)encrypt));  
	MD5Final(&md5,decrypt);   

	printf("加密前:%s\n加密后16位:",encrypt);  
	for(i=4;i<12;i++)  
	{  
	    printf("%02x",decrypt[i]);  //02x前需要加上 %  
	}  
	   
	printf("\n加密前:%s\n加密后32位:",encrypt);  
	for(i=0;i<16;i++)  
	{  
	    printf("%02x",decrypt[i]);  //02x前需要加上 %  
	}  

	getchar();  

	return 0;  
}  

