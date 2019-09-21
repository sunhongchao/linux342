
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
	wait(0);//�����ӽ��̣������ӽ��̽�������Ϊ��ʬ���̡�һ�λ���һ���ӽ���
}
int main(void)
{
	//���ں˵Ǽ��źŴ������Լ��ź���ֵ
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal sigchld error");
	}
	
	pid_t pid;
	pid=fork();
	if(pid<0){
		perror("fork error");
		exit(1);	
	}else if(pid>0){
		out(100);
	}else{
		out(10);
	}
	
	return 0;
}

