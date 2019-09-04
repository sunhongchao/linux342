#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"


#define FILE_PATH      "./test.txt"
int main(int argc,char *argv[])
{
	char buf[512];
	int len;
	memset(buf,0,512);
	if( (len = read_all_file_data(FILE_PATH, buf, 512) ) == -1)
		printf("read_all_file_data() fail\n");
	printf("file len:%d \n file content:\n",len);
	printf("%s\n",buf);
	memset(buf,0,512);
	if( (len = read_file_data(FILE_PATH, buf, 32) ) == -1)
		printf("read_file_data() fail\n");
	printf("file len:%d \n file content:\n",len);
	printf("%s\n",buf);
}
