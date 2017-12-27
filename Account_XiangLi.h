// Account class
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
	Account();// constructor

			  // using template design patter
	virtual void printHistory() = 0;// print the transaction history

protected:
	double cashBalance;
};

#endif

