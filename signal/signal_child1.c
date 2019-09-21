
/*
							程序实验
   子进程结束后产生SIGCHLD信号，父进程接收到该信号后
回收子进程，避免僵尸进程。
可以打开一个新的终端执行下面命令
 ps -aux | grep child 查看进程。z表示僵尸进程
4661  0.0  0.0      0     0 pts/1    Z+   17:29   0:00 [signal_child] 
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
void out(int n)
{
	int i=1;
	for(;i<=n;i++){
		printf("%d out %d\n",getpid(),i);
		sleep(1);
	}
}
//定义信号处理函数
void sig_handler(int signo)
{
	printf("child process deaded,signo:%d %d\n",getpid(),signo);
	wait(0);//回收子进程，否则子进程结束后会成为僵尸进程
}
int main(void)
{
	//向内核登记信号处理函数以及信号量值
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal sigchld error");
	}
	
	int i=0;
     pid_t pid;
     for(;i<2;i++)
	{

		pid=fork();
         if(pid<0)
         {
           perror("fork error");
           exit(1);
        } else 
		if(pid==0)
		{
             if(i==0)//child1 
			 { 
                out(10);
                 break;
             }
             if(i==1)//child2 
			 { 
                 out(20);
                 break;
             }
         }else
     	 {//parent 
        	 if(i==1)
			{
           	 out(100);
         	}
		 }
	}
	
	return 0;
}

