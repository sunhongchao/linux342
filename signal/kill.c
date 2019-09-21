
/*
	kill -l 命令查看所有信号						
  kill() 向指定进程发送信号，raise()向自己发送信号
int kill(pid_t pid,int signo)
raise(int signo);
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

//定义信号处理函数
void sig_handler(int signo)
{
	printf("Reveive Signo:%d\n",signo);
	
}
int main(void)
{
	//向内核登记信号处理函数以及信号量值
	if(signal(SIGUSR1,sig_handler)==SIG_ERR){
		perror("signal SIGUSR1 error");
	}
	if(signal(SIGUSR2,sig_handler)==SIG_ERR){
		perror("signal SIGUSR2 error");
	}
 	int i=0;
	while(i<10){
		printf("%d out %d\n",getpid(),i++);
		sleep(1);
	}
	raise(SIGUSR1);
	kill(getpid(),SIGUSR2);
		i=0;
	while(i<10){
		if(i==5)
			kill(getpid(),SIGKILL);//发送信号结束本进程
		printf("%d out %d\n",getpid(),i++);
		sleep(1);
	}
	
	
	
	return 0;
}

