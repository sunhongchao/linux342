#include"account.h"
#include<malloc.h>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
typedef struct{
	char name[20];
	Account *account;
	double amt;//取款金额
}OperArg;
void *withdraw_fn(void *arg)
{
	OperArg *oa=(OperArg*)arg;
	
	double amt=withdraw(oa->account,oa->amt);
	printf("%8s(0x%lx) withdraw %f from account %d\n",
			oa->name,pthread_self(),amt,oa->account->code);
	return(void *)0;
}
void *deposit_fn(void *arg)
{
	OperArg *oa=(OperArg*)arg;
	double amt=deposit(oa->account,oa->amt);
	printf("%8s(0x%lx) withdraw %f from account %d\n",
			oa->name,pthread_self(),amt,oa->account->code);
	return(void *)0;
}
//查看银行账户线程函数
void *check_fn(void *arg)
{
	OperArg *oa=(OperArg*)arg;
	double balance=get_balance(oa->account);
	printf("%8s(0x%lx) balance %f from account %d\n",
			oa->name,pthread_self(),balance,oa->account->code);
	return(void *)0;
}
int main(void)
{
	int err;
	pthread_t boy,girl;
	Account *a=create_account(100001,10000);
	OperArg o1,o2;
	strcpy(o1.name,"boy");
	o1.account=a;
	o1.amt=10000;
	strcpy(o2.name,"girl");
	o2.account=a;
	o2.amt=10000;

	if((err=pthread_create(&boy,NULL,withdraw_fn,(void*)&o1))!=0){
		perror("pthread_creat error");	
	}
	if((err=pthread_create(&girl,NULL,withdraw_fn,(void*)&o2))!=0){
		perror("pthread_creat error");	
	}
	pthread_join(boy,NULL);
	pthread_join(girl,NULL);
	printf("account balance:%f\n",get_balance(a));
	destroy_account(a);

}