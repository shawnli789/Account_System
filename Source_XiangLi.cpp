#include<iostream>
#include<time.h>
#include<fstream>
#include<sstream>
#include <cstdlib>

#include "Account_XiangLi.h"
#include "StockAccount_XiangLi.h"
#include "BankAccount_XiangLi.h"

using namespace std;

int main() {
// menu choices
	int choice1, choice2;

// stock account
	string symbol;// stock name
	int number;// number of shares of stock to buy or sell
	double max_money;// max money per stock to buy
	double min_money;// min money per stock to sell

// bank account
	double money;// money to deposite and withdraw

// class objects
	StockAccount stock;
	BankAccount bank;

	while (1)
	{
	MainMenu:
		cout << "Welcome to the Account Management System!\nPlease select an account to access:\n" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "0. Exit" << endl;
		cout << "\nYour Option: ";
		cin >> choice1;
		switch (choice1)
		{
		case 1:
		{
			cout << "You logged into your stock account. Please select the operation: " << endl;
			while (1) {
				cout << "\n(Stock Portfolio Account)" << endl;
				cout << "1. Display the price for a stock symbol\n";
				cout << "2. Display the current portfolio\n";
				cout << "3. Buy Shares\n";
				cout << "4. Sell Shares\n";
				cout << "5. View a graph for the portfolio value\n"; // MATLAB
				cout << "6. View transaction history\n";
				cout << "0. Return to previous Menu\n";
				cout << "\nYour Option: ";
				cin >> choice2;
				switch (choice2) {
				case 1:
					cout << "Please enter the stock symbol:";
					cin >> symbol;
					stock.displayPrice(symbol);
					break;

				case 2:
					stock.displayCurrentPortfolio();
					break;

				case 3:
					cout << "Please enter the stock symbol you wish to purchase: ";
					cin >> symbol;
					cout << "Please enter the number of shares you are purchasing: ";
					cin >> number;
					cout << "Please enter the maximum amount you are willing to pay per share: ";
					cin >> max_money;
					stock.buyShare(symbol, number, max_money);
					break;

				case 4:
					cout << "Please enter the stock symbol you wish to sell: ";
					cin >> symbol;
					cout << "Please enter the number of shares you are selling: ";
					cin >> number;
					cout << "Please enter the minimun amount you are willing to sell per share: ";
					cin >> min_money;
					stock.sellShare(symbol, number, min_money);
					break;
				case 5:
					stock.viewGraph();
					break;
				case 6:
					stock.printHistory();
					break;
				case 0:
					cout << endl;
					goto MainMenu;
				default:
					cout << "Sorry, It's invalid option! Please chose again."<< endl;
					break;
				}
			}
		}

		case 2:
		{
			cout << "You logged into your bank account. Please select the operation: " << endl;
			while (1) {
				cout << "\n(Bank Account)" << endl;
				cout << "1. View account balance\n";
				cout << "2. Deposit money\n";
				cout << "3. Withdraw money\n";
				cout << "4. Print out history\n";
				cout << "0. Return to previous menu\n";
				cout << "\nYour Option: ";
				cin >> choice2;
				switch (choice2)
				{
				case 1:
					bank.viewAccountBalance();
					break;
				case 2:
					cout << "Please enter the amount of money you want to deposit: ";
					cin >> money;
					bank.deposit(money);
					break;
				case 3:
					cout << "Please enter the amount of money you want to withdraw: ";
					cin >> money;
					bank.withdraw(money);
					break;
				case 4:
					bank.printHistory();
					break;
				case 0:
					cout << endl;
					goto MainMenu;
				default:
					cout << "Sorry, It's invalid option! Please chose again." << endl;
					break;
				}
			}
		case 0:
			return 0;
		default:
			cout << "Sorry, It's invalid option! Please chose again." << endl;
			break;
		}
		}
	}
}
