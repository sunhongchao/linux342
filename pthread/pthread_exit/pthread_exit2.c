#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
	int d1;
	int d2;
}Arg;
void *th_fn(void *arg)
{
	Arg *r=(Arg*)arg;
	
	return (void*)(r);
}
int main(void)
{
	int err;
	pthread_t th;
	Arg r={20,50};
	if((err=pthread_create(&th,NULL,th_fn,(void*)&r))!=0){
		perror("pthread_creat error");	
	}
	int *result;
	pthread_join(th,(void**)&result);
	printf("result is %d\n",((Arg*)result)->d1+((Arg*)result)->d2);
	printf("control thread id:%lx\n",pthread_self());
	printf("finished!\n");
	exit(0);
}
