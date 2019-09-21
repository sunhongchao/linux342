/*
alarm()  ��������
ualarm() ������΢��
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<math.h>
//�����źŴ�����
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
			alarm(0);//ȡ����ʱ��
		sleep(1);
	}
}
int main(void)
{
	//���ں˵Ǽ��źŴ������Լ��ź���ֵ
	if(signal(SIGALRM,sig_handler)==SIG_ERR){
		perror("signal SIGALRM error");
	}
	alarm(1);
	printf("begin running main\n");
	out_data();
	printf("end running main\n");
	
	return 0;
}

