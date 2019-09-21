#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
sem_t sem1;
sem_t sem2;
void *a_fn(void *arg)
{
	sem_wait(&sem1);
	printf("thread a running\n");
	return (void*)0;
}
void *b_fn(void *arg)
{
	sem_wait(&sem2);
	printf("thread b running\n");
	sem_post(&sem1);//线程a运行
	return (void*)0;
}
void *c_fn(void *arg)
{
	printf("thread c running\n");
	sem_post(&sem2);//线程b运行
	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t a,b,c;
	sem_init(&sem1,0,0);//初始为0，线程阻塞
	sem_init(&sem2,0,0);
	if((err=pthread_create(&a,NULL,a_fn,(void*)0))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&b,NULL,b_fn,(void*)0))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&c,NULL,c_fn,(void*)0))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(a,NULL);
	pthread_join(b,NULL);
	pthread_join(c,NULL);
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	return 0;

}