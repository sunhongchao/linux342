/*
alarm是进程资源，作用范围为单一进程。无论在主控线程还是子线程调用signal
()注册alarm信号处理函数。信号默认都发送给主控线程，只有在主控线程屏蔽
alarm信号，才能由子线程接收到

信号发生时：
慢速系统调用会重新启动，如read
而sleep()等函数会中断执行，信号处理完毕执行sleep下面的代码，sleep不会再执行，即使睡眠时间还没有到。

*/

/*
 程序说明：
	主控线程启动两个子线程th,th2;并屏蔽alarm信号。然后由th接收alarm信号
   th2运行5s后发送phread_cancel 停止线程th
  

*/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void sig_handler(int signo)
{
	printf("pthread id in the sig_handler: %lx\n",
				pthread_self());
	if(signo==SIGALRM){
		printf("timeout...\n");
	}
	alarm(2);
}
void *th_fn(void *arg)
{
	if(signal(SIGALRM,sig_handler)==SIG_ERR){
		perror("signal sigalrm error");
	}
	alarm(2);
	int i;
	for(i=0;i<=100;i++){
		printf("(%lx) i:%d\n",pthread_self(),i);
		sleep(1);
	}
	return (void*)0;
}
//终止线程th
void *th2_fn(void *arg)
{
    pthread_t th =(pthread_t)arg;
	int i;
	for(i=0;i<=15;i++){
		if(i==5){
			pthread_cancel(th);
			alarm(0);//取消alarm闹钟定时器
		}
		printf("(%lx) i: %d\n",pthread_self(),i);
		sleep(1);
	}
	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t th,th2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,
				PTHREAD_CREATE_DETACHED);
	if((err=pthread_create(&th,&attr,th_fn,(void*)0))!=0){
		perror("pthread_creat error");	
		
	}
	if((err=pthread_create(&th2,&attr,th2_fn,(void*)th))!=0){
		perror("pthread_creat error");	
		
	}
	//主控线程屏蔽alarm信号,
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	//最好方式是先读旧的信号屏蔽字，该后设置
	pthread_sigmask(SIG_SETMASK,&set,NULL);
	while(1)
	{
		printf("control thread(%lx) is running....\n",
			pthread_self());
		sleep(10);
	}
	printf("control thread over\n");
	return 0;

}