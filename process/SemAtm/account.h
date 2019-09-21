#ifndef __ACCOUNT_H
#define __ACCOUNT_H
typedef struct
{
	int code;
	double balance;
	int semid;
}Account;
extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double amt);
extern double get_balance(Account *a);
#endif
