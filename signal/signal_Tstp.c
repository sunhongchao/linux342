/*                    
						笔记
	SIGTSTP:交互式停止信号，暂停信号，用户在终端上按下挂起键ctrl+z
	SIGINT:用户按下中断键Ctrl+c
    也可以在终端发送命令产生信号：
	kill -SIGTSTP 进程pid
	kill -SIGINT  进程pid
	查看系统所有信号：
	1、vim /usr/include/bits/signum.h
    2、终端执行命令 kill -l 

	
*/


/*
							程序实验
    1、ctrl+z 暂停程序
	2、kill -SIGCONT pid   继续运行程序
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
//定义信号处理函数
void sig_handler(int signo)
{
	printf("%d,%d occured\n",getpid(),signo);
}
int main(void)
{
	//向内核登记信号处理函数以及信号量值
	/*(if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal error");
	}
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("signal error");
	}*/
	int i=0;
	while(i<30){
		printf("%d out %d\n",getpid(),i++);
		sleep(1);
	}
	return 0;
}