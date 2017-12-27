#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Account_XiangLi.h"

class BankAccount :public Account
{
public:
	BankAccount();
	void viewAccountBalance();
	void deposit(double);
	void withdraw(double);
	virtual void printHistory();
};
#endif // !BANKACCOUNT_H

