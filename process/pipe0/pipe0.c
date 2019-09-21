#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void)
{
    int fd[2];
    if(pipe(fd)<0){
        perror("pipe error");
        exit(1);
    }
    pid_t pid;
    if((pid=fork())<0){
       perror("fork error");
       exit(1);
    }else if(pid>0){//父进�?
       close(fd[0]);
       int start=1,end=100;
       if(write(fd[1],&start,sizeof(int))!=sizeof(int)){
           perror("write error");
           exit(1);
       }
       if(write(fd[1],&end,sizeof(int))!=sizeof(int)){
           perror("write error");
           exit(1);
       }
       close(fd[1]);
	wait(0);
    }else{//子进�?

        close(fd[1]);
        int start=0,end=0;
        if(read(fd[0],&start,sizeof(int))<0){
            perror("read error");
            exit(1);
        }
        if(read(fd[0],&end,sizeof(int))<0){
            perror("read error");
            exit(1);
        }
        close(fd[0]);
        printf("child process read start:%d,end:%d\n",start,end);
    }
    exit(0);

}
