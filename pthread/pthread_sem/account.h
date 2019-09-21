#ifndef __ACCOUNT_H
#define __ACCOUNT_H
#include<pthread.h>
#include<semaphore.h>
typedef struct
{
	int code;
	double balance;
	sem_t sem;//对共享资源加锁
}Account;
extern Account* create_account(int code,double balance);
extern void destroy_account(Account *a);
extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double amt);
extern double get_balance(Account *a);
#endif