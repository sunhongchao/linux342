#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
typedef struct
{
	int res;
	sem_t sem;
}Result;
//计算并将结果放置Result中的线程运行函数
void *set_fn(void *arg)
{
	Result *r=(Result*)arg;
	int i=1,sum=0;
	for(;i<=100;i++){
		sum+=i;
	}
	r->res=sum;
	sem_post(&r->sem);
	return (void*)0;
}
void *get_fn(void *arg)
{
	Result *r=(Result*)arg;
	sem_wait(&r->sem);
	//获取结果
	int res=r->res;
	
	printf("0x%lx get sum is %d\n",pthread_self(),res);
	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t cal,get;
	Result r;
    sem_init(&r.sem,0,0);//初始为0，线程阻塞
	if((err=pthread_create(&cal,NULL,set_fn,(void*)&r))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&get,NULL,get_fn,(void*)&r))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(cal,NULL);
	pthread_join(get,NULL);
	sem_destroy(&r.sem);
	return 0;

}