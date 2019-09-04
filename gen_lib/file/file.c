
#include <stdio.h>
#include <string.h>
#include <errno.h>
/*
	功能：	将文件全部内容读取到单个缓冲区
	参数： 	path	文件路径，包含文件名
			buf	    缓冲区
	返回值：-1		失败，
			>= 0 	实际读取的子节数
*/
int read_all_file_data(char *path, char *buf, int len)
{
	int file_size = 0,real_len = 0;
    if (path == NULL || buf == NULL){
		printf("path or buf is NULL\n");
        return -1;
    }

    FILE *fp = fopen(path, "r");    
    if(fp == NULL) {
		perror("fopen");
        return -1;
    }
    //求得文件的大小  
    if(fseek(fp, 0, SEEK_END) == -1){
		perror("fseek");
		fclose(fp);
		return -1;
	}
    file_size = ftell(fp);
	if(file_size > len) {
		printf("buf is too small to stoure file data\n");
		fclose(fp);
		return -1;
		
	}
	errno = 0;
    rewind(fp);
	if(errno){
		perror("rewind");
		fclose(fp);
		return -1;
	}
	/*读取的文件大小是计算出来的，因此不存在提前读到EOF的情况*/
    real_len = fread(buf, sizeof(char), file_size, fp);
	if(ferror(fp)){
		printf("errro on fp!\n");
		clearerr(fp);
		fclose(fp);
		return -1;
	}
    fclose(fp);
    return real_len;
}
/*
	功能：	从文件读取len子节长度数据到缓冲区
	参数： 	path	文件路径，包含文件名
			buf	    缓冲区
			len      长度
	返回值：
			-1		 失败
			>= 0 	实际读取的子节数
*/
int read_file_data(char *path, char *buf,int len)
{
	int file_size = 0,real_len = 0;
    if (path == NULL || buf == NULL){
		printf("path or buf is NULL\n");
        return -1;
    }

    FILE *fp = fopen(path, "r");    
    if(fp == NULL) {
		perror("fopen");
        return -1;
    }

    //求得文件的大小  
    if(fseek(fp, 0, SEEK_END) == -1){
		perror("fseek");
		fclose(fp);
		return -1;
	}
	file_size = ftell(fp);
	errno = 0;
    rewind(fp);
	if(errno){
		perror("rewind");
		fclose(fp);
		return -1;
	}
	if(file_size >= len) {
		real_len = fread(buf, sizeof(char), len, fp);
	} else {
		 real_len = fread(buf, sizeof(char), file_size, fp);
	}
	if(ferror(fp)){
		printf("errro on fp!\n");
		clearerr(fp);
		fclose(fp);
		return -1;
	}
    fclose(fp);
    return real_len;
	
}
