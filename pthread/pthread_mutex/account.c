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
	//¶Ô»¥³âËø³õÊ¼»¯
	pthread_mutex_init(&a->mutex,NULL);
	return a;
}
void destroy_account(Account *a)
{
	assert(a!=NULL);
	//Ïú»Ù»¥³âËø
	pthread_mutex_destroy(&a->mutex);
	free(a);
}
double withdraw(Account *a,double amt)
{
	assert(a!=NULL);
	pthread_mutex_lock(&a->mutex);
	if(amt<0||amt>a->balance){
		pthread_mutex_unlock(&a->mutex);
		return 0.0;
		}
	
	double balance=a->balance;
	sleep(1);
	balance-=amt;
	a->balance=balance;
	pthread_mutex_unlock(&a->mutex);
	return amt;
}
double deposit(Account *a,double amt)
{
	assert(a!=NULL);
	pthread_mutex_lock(&a->mutex);
	if(amt<0)
	{
		pthread_mutex_unlock(&a->mutex);
		return 0.0;
	}
	double balance=a->balance;
	sleep(1);
	balance+=amt;
	a->balance=balance;
	pthread_mutex_unlock(&a->mutex);
	return amt;
}
double get_balance(Account *a)
{
	assert(a!=NULL);
	pthread_mutex_lock(&a->mutex);
	double balance=a->balance;
	pthread_mutex_unlock(&a->mutex);
	return balance;
}