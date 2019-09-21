#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
	int value;
	int r_wait;//用户给出用于判断的条件
	pthread_cond_t rc;//写着唤醒读者的条件变量
	pthread_mutex_t rm;

	int w_wait;
	pthread_cond_t wc;
	pthread_mutex_t wm;
	
}Storage;
void set_data(Storage *s,int value)
{
	s->value=value;
}
int get_data(Storage *s)
{
	return s->value;
}
//计算并将结果放置Result中的线程运行函数
void *set_fn(void *arg)
{
	Storage *s=(Storage*)arg;
	int i=1,sum=0;
	for(;i<=100;i++){
		set_data(s,i+100);
		printf("0x%lx(%-5d) write data: %d\n",pthread_self(),i,i+100);
		while(!s->r_wait){
			pthread_mutex_unlock(&s->rm);
			sleep(1);
			pthread_mutex_lock(&s->rm);
		}
		s->r_wait=0;//下次读写准备
		pthread_mutex_unlock(&s->rm);
		//唤醒等待结果的那个线程
		pthread_cond_broadcast(&s->rc);
		
		
		pthread_mutex_lock(&s->wm);
		s->w_wait=1;
		//写者线程阻塞等待被读者线程唤醒，然后重新开始写数据
		pthread_cond_wait(&s->wc,&s->wm);
		pthread_mutex_unlock(&s->wm);
	}
	
	
	return (void*)0;
}
void *get_fn(void *arg)
{
	Storage *s=(Storage*)arg;
	int i=1;
	for(;i<=100;i++){
		pthread_mutex_lock(&s->rm);
		s->r_wait=1;
		//线程阻塞等待被唤醒pthread_cond_wait内部会释放互斥锁
		pthread_cond_wait(&s->rc,&s->rm);
		int value=get_data(s);
		pthread_mutex_unlock(&s->rm);
		printf("0x%lx(%-5d) read data: %d\n",pthread_self(),i,value);
		
		
		pthread_mutex_lock(&s->wm);
		while(!s->w_wait){
			pthread_mutex_unlock(&s->wm);
			sleep(1);
			pthread_mutex_lock(&s->wm);
		}
		s->w_wait=0;
		pthread_mutex_unlock(&s->wm);
		//唤醒写者线程
		pthread_cond_broadcast(&s->wc);
		
	}
	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t rth,wth;
	Storage s;
	s.r_wait=0;
	s.w_wait=0;
	pthread_cond_init(&s.rc,NULL);
	pthread_mutex_init(&s.rm,NULL);	
	pthread_cond_init(&s.wc,NULL);
	pthread_mutex_init(&s.wm,NULL);

	if((err=pthread_create(&rth,NULL,set_fn,(void*)&s))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&wth,NULL,get_fn,(void*)&s))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(rth,NULL);
	pthread_join(wth,NULL);
	pthread_cond_destroy(&s.rc);
	pthread_mutex_destroy(&s.rm);
	pthread_cond_destroy(&s.wc);
	pthread_mutex_destroy(&s.wm);
	return 0;

}