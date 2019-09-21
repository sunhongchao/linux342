#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/shm.h>
#include"tell.h"
int main(void)
{
	int shmid;
	if((shmid=shmget(IPC_PRIVATE,1024,IPC_CREAT|IPC_EXCL|0X777))<0){
	    perror("shmget error");
		exit(1);	
	}
	pid_t pid;
	init();
	if((pid=fork())<0){
	    perror("fork error");	
	    exit(1);
	}else if(pid>0){ //parent process
		int *pi=(int*)shmat(shmid,0,0);
		if(pi==(int*)-1){
			perror("shmat error");
			exit(1);		
		}
		*pi=100;*(pi+1)=20;	
		shmdt(pi);	
		notify_pipe();
		destroy_pipe();
		wait(0);	
	}else{//child process
	    wait_pipe();//wait parent process write done;
        int *pi=(int*)shmat(shmid,0,0);
		if(pi==(int*)-1){
			perror("shmat error");
			exit(1);		
		}
		printf("start:%d,end:%d\n",*pi,*(pi+1));
		shmdt(pi);
		shmctl(shmid,IPC_RMID,NULL);
		destroy_pipe();
         
	}
	exit(0);

}
