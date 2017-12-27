#include<iostream>
#include<fstream>

#include "Account_XiangLi.h"// class Account definition
using namespace std;

// constructor: read the current account information
Account::Account()
{
	ifstream Account;
	Account.open("Cash_Balance.txt");// open the txt Cash_Balance
	if (!Account.is_open())// if not, initialize the cashbalance
	{
		cashBalance = 10000;
	}
	else
		Account >> cashBalance;// read the cash balance from the file
}