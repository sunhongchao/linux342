
/*
	kill -l ����鿴�����ź�						
  kill() ��ָ�����̷����źţ�raise()���Լ������ź�
int kill(pid_t pid,int signo)
raise(int signo);
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

//�����źŴ�����
void sig_handler(int signo)
{
	printf("Reveive Signo:%d\n",signo);
	
}
int main(void)
{
	//���ں˵Ǽ��źŴ������Լ��ź���ֵ
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
			kill(getpid(),SIGKILL);//�����źŽ���������
		printf("%d out %d\n",getpid(),i++);
		sleep(1);
	}
	
	
	
	return 0;
}

