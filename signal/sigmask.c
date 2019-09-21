/*
����ĳ���ź�ʱ�����ź��ź�����������Ϊ1
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
//�����źŴ�����
void sig_handler(int signo)
{
	printf("begin process the %d\n",signo);
	sigset_t oset;
	sigemptyset(&oset);
	//��ȡ�ź���������
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	//����ĳ���ź�ʱ�����ź��ź�����������Ϊ1,��ʱ���������������
	out_set(oset);
	printf("finish process the %d\n",signo);
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
	sigset_t oset;
	printf("befor signal occured mask:\n");
	sigemptyset(&oset);
	//��ȡ�ź���������
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	out_set(oset);
	printf("process %d wait signal...\n",getpid());
	pause();//�����źź���жϸú���ִ�У��źŴ�����ϳ�������ִ��
	printf("after signal occured mask:\n");
	sigemptyset(&oset);
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		perror("sigprocmask error");	
	}
	out_set(oset);

	return 0;
}

