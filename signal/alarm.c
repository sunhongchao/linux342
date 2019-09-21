/*
alarm()  精度是秒
ualarm() 精度是微妙
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<math.h>
//定义信号处理函数
void sig_handler(int signo)
{
	if(signo==SIGALRM){
		printf("clock time out\n");
		alarm(1);
	}
}
void out_data(void)
{
	int i=1;
	while(i<=20){
		double d=drand48();
		printf("%-10d:%lf\n",i++,d);
		if(i==15)
			alarm(0);//取消定时器
		sleep(1);
	}
}
int main(void)
{
	//向内核登记信号处理函数以及信号量值
	if(signal(SIGALRM,sig_handler)==SIG_ERR){
		perror("signal SIGALRM error");
	}
	alarm(1);
	printf("begin running main\n");
	out_data();
	printf("end running main\n");
	
	return 0;
}

