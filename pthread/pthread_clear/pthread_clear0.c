#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void clean_fun(void *arg)
{
	char *s=(char*)arg;
	printf("clean_fun:%s\n",s);
}
/*
  execute=1执行线程清理函数，否则不执行，执行函数顺序为：先入后执行。
清理函数在线程结束时执行
*/
void *th_fun(void*arg)
{
	int execute=(int)arg;
	pthread_cleanup_push(clean_fun,"first clean func");
	pthread_cleanup_push(clean_fun,"second clean func");
	printf("thread running%lx\n",pthread_self());
	pthread_cleanup_pop(execute);
	pthread_cleanup_pop(execute);

	return (void*)0;
}
int main(void)
{
	int err;
	pthread_t th1,th2;
	if((err=pthread_create(&th1,NULL,th_fun,(void*)1))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(th1,NULL);
	printf("th1(%lx) finished\n",th1);

	if((err=pthread_create(&th2,NULL,th_fun,(void*)0))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(th2,NULL);
	printf("th2(%lx) finished\n",th2);


}