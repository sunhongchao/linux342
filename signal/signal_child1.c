
/*
							����ʵ��
   �ӽ��̽��������SIGCHLD�źţ������̽��յ����źź�
�����ӽ��̣����⽩ʬ���̡�
���Դ�һ���µ��ն�ִ����������
 ps -aux | grep child �鿴���̡�z��ʾ��ʬ����
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
//�����źŴ�����
void sig_handler(int signo)
{
	printf("child process deaded,signo:%d %d\n",getpid(),signo);
	wait(0);//�����ӽ��̣������ӽ��̽�������Ϊ��ʬ����
}
int main(void)
{
	//���ں˵Ǽ��źŴ������Լ��ź���ֵ
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

