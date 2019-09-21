/*
发生某个信号时，该信号信号屏蔽字设置为1
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<math.h>
void out_set(sigset_t set)
{
	int i=1;
	for(;i<31;i++){
		if(sigismember(&set,i)){
			printf("%d\n",i);
		}
	}
}
//定义信号处理函数
void sig_handler(int signo)
{
	printf("begin process the %d\n",signo);
	sigset_t oset;
	sigemptyset(&oset);
	//获取信号屏蔽内容
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	//发生某个信号时，该信号信号屏蔽字设置为1,此时输出屏蔽字有内容
	out_set(oset);
	printf("finish process the %d\n",signo);
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
	sigset_t oset;
	printf("befor signal occured mask:\n");
	sigemptyset(&oset);
	//获取信号屏蔽内容
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	out_set(oset);
	printf("process %d wait signal...\n",getpid());
	pause();//发生信号后会中断该函数执行，信号处理完毕程序向下执行
	printf("after signal occured mask:\n");
	sigemptyset(&oset);
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	out_set(oset);

	return 0;
}

