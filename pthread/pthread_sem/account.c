#include"account.h"
#include<malloc.h>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
Account* create_account(int code,double balance)
{
	Account *a=(Account*)malloc(sizeof(Account));
	assert(a!=NULL);
	a->code=code;
	a->balance=balance;
	sem_init(&a->sem,0,1);//初始为1，有一个取款线程可以执行
	return a;
}
void destroy_account(Account *a)
{
	assert(a!=NULL);
	//销毁互斥锁
	sem_destroy(&a->sem);
	free(a);
}
double withdraw(Account *a,double amt)
{
	assert(a!=NULL);
	sem_wait(&a->sem);
	if(amt<0||amt>a->balance){
		sem_post(&a->sem);
		return 0.0;
		}
	
	double balance=a->balance;
	sleep(1);
	balance-=amt;
	a->balance=balance;
	sem_post(&a->sem);
	return amt;
}
double deposit(Account *a,double amt)
{
	assert(a!=NULL);
	sem_wait(&a->sem);
	if(amt<0)
	{
		sem_post(&a->sem);
		return 0.0;
	}
	double balance=a->balance;
	sleep(1);
	balance+=amt;
	a->balance=balance;
	sem_post(&a->sem);
	return amt;
}
double get_balance(Account *a)
{
	assert(a!=NULL);
	sem_wait(&a->sem);
	double balance=a->balance;
	sem_post(&a->sem);
	return balance;
}