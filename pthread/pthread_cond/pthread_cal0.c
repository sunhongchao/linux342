#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	int res;
	int is_wait;//�û����������жϵ�����
	pthread_cond_t cond;//�ȴ����������������ȴ��߳����ڵȴ�������
	pthread_mutex_t mutex;
}Result;
//���㲢���������Result�е��߳����к���
void *set_fn(void *arg)
{
	Result *r=(Result*)arg;
	int i=1,sum=0;
	for(;i<=100;i++){
		sum+=i;
	}
	r->res=sum;
	//�жϻ�ý�����߳��Ƿ�׼���ã�û�������ߵȴ�.������������Ҳ�ǻ���
	pthread_mutex_lock(&r->mutex);
	while(!r->is_wait){
		pthread_mutex_unlock(&r->mutex);
		usleep(100);
		pthread_mutex_lock(&r->mutex);
	}
	pthread_mutex_unlock(&r->mutex);
	//���ѵȴ�������Ǹ��߳�
	pthread_cond_broadcast(&r->cond);
	
	return (void*)0;
}
void *get_fn(void *arg)
{
	Result *r=(Result*)arg;
	pthread_mutex_lock(&r->mutex);
	r->is_wait=1;//��ȡ������߳��Ѿ�׼����
	pthread_cond_wait(&r->cond,&r->mutex);//�߳������ȴ�������
	//��ȡ���
	int res=r->res;
	pthread_mutex_unlock(&r->mutex);
	printf("0x%lx get sum is %d\n",pthread_self(),res);
	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t cal,get;
	Result r;
	r.is_wait=0;
	pthread_cond_init(&r.cond,NULL);
	pthread_mutex_init(&r.mutex,NULL);
	if((err=pthread_create(&cal,NULL,set_fn,(void*)&r))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&get,NULL,get_fn,(void*)&r))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(cal,NULL);
	pthread_join(get,NULL);
	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);
	return 0;

}