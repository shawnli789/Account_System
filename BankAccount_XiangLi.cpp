#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<iomanip>
#include<time.h>  
#include<fstream>  
#include<string>
#include<stdlib.h>
#include<sstream>

#include "BankAccount_XiangLi.h"

using namespace std;

// constructor
BankAccount::BankAccount()
	:Account()
{
	// empty body
}

// print the cash balance
void BankAccount::viewAccountBalance()
{
	ifstream cash("Cash_Balance.txt");// read from before
	cash >> Account::cashBalance;
	cash.close();

	cout << "You have $" << Account::cashBalance << " in your bank account" << endl;
}

// add deposit
void BankAccount::deposit(double amount)
{
	if (amount <= 0)
		cout << "Invalid amount." << endl;
	else
	{
		ifstream cash("Cash_Balance.txt");// read from before
		cash >> Account::cashBalance;
		cash.close();

		Account::cashBalance += amount;

		ofstream cash1;
		cash1.open("Cash_Balance.txt");
		cash1 << Account::cashBalance << endl;
		cash1.close();

		// add to history
		ofstream Bank;
		Bank.open("Bank_transaction_history.txt", ios::app);
		if (Bank.is_open())
		{
			struct tm *local;
			time_t t = time(0);
			local = localtime(&t);
			Bank << "Deposit\t" << amount << "\t" << (local->tm_mon) + 1 << "/" << local->tm_mday << "/" << (local->tm_year) + 1900 << "\t"
				<< Account::cashBalance << endl;
		}
		else
			cout << "Unable to open bank_transaction_history.txt" << endl;
	}
}

// withdraw money
void BankAccount::withdraw(double amount)
{
	if (amount <= 0)
		cout << "Invalid amount." << endl;

	//if money is not enough,reaturn false
	if (amount > Account::cashBalance)
		cout << "Error, the balance of the account is not sufficient to withdraw." << endl;
	else
	{
		ifstream cash("Cash_Balance.txt");// read from before
		cash >> Account::cashBalance;
		cash.close();

		Account::cashBalance -= amount;

		ofstream cash1;
		cash1.open("Cash_Balance.txt");
		cash1 << Account::cashBalance << endl;
		cash1.close();

		// add to history
		ofstream Bank;
		Bank.open("Bank_transaction_history.txt", ios::app);
		if (Bank.is_open())
		{
			struct tm *local;
			time_t t = time(0);
			local = localtime(&t);

			Bank << "Withdraw\t" << amount << "\t" << (local->tm_mon) + 1 << "/" << local->tm_mday << "/" << (local->tm_year) + 1900 << "\t"
				<< Account::cashBalance << endl;
		}
		else
			cout << "Unable to open bank_transaction_history.txt" << endl;
	}
}

// print bank account transaction
void BankAccount::printHistory()
{
	ifstream History("Bank_transaction_history.txt");
	string events, date;
	double amount, balance;

	if (History.is_open())
	{
		cout << left << setw(13) << "Event" << setw(14) << "Amount" << setw(12) << "Date" << setw(10) << "Balance" << endl;
		while (History >> events >> amount >> date >> balance)
		{
			cout << left << setw(13) << events << "$" << setw(13) << amount << setw(12) << date << "$" << setw(10) << balance << endl;
		}
		History.close();
	}
	else
		cout << "Unable to print out history." << endl;
}