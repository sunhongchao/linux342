/*
alarm�ǽ�����Դ�����÷�ΧΪ��һ���̡������������̻߳������̵߳���signal
()ע��alarm�źŴ��������ź�Ĭ�϶����͸������̣߳�ֻ���������߳�����
alarm�źţ����������߳̽��յ�

�źŷ���ʱ��
����ϵͳ���û�������������read
��sleep()�Ⱥ������ж�ִ�У��źŴ������ִ��sleep����Ĵ��룬sleep������ִ�У���ʹ˯��ʱ�仹û�е���

*/

/*
 ����˵����
	�����߳������������߳�th,th2;������alarm�źš�Ȼ����th����alarm�ź�
   th2����5s����phread_cancel ֹͣ�߳�th
  

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
//��ֹ�߳�th
void *th2_fn(void *arg)
{
    pthread_t th =(pthread_t)arg;
	int i;
	for(i=0;i<=15;i++){
		if(i==5){
			pthread_cancel(th);
			alarm(0);//ȡ��alarm���Ӷ�ʱ��
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
	//�����߳�����alarm�ź�,
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	//��÷�ʽ���ȶ��ɵ��ź������֣��ú�����
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