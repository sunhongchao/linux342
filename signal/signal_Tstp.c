/*                    
						�ʼ�
	SIGTSTP:����ʽֹͣ�źţ���ͣ�źţ��û����ն��ϰ��¹����ctrl+z
	SIGINT:�û������жϼ�Ctrl+c
    Ҳ�������ն˷�����������źţ�
	kill -SIGTSTP ����pid
	kill -SIGINT  ����pid
	�鿴ϵͳ�����źţ�
	1��vim /usr/include/bits/signum.h
    2���ն�ִ������ kill -l 

	
*/


/*
							����ʵ��
    1��ctrl+z ��ͣ����
	2��kill -SIGCONT pid   �������г���
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
//�����źŴ�����
void sig_handler(int signo)
{
	printf("%d,%d occured\n",getpid(),signo);
}
int main(void)
{
	//���ں˵Ǽ��źŴ������Լ��ź���ֵ
	/*(if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal error");
	}
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("signal error");
	}*/
	int i=0;
	while(i<30){
		printf("%d out %d\n",getpid(),i++);
		sleep(1);
	}
	return 0;
}