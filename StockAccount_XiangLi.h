#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include<string>
using namespace std;

#include "Account_XiangLi.h"

// Node class
class Node
{
	friend class StockAccount;
public:
	Node(string &, int, double);// initialize name, number of shares and price
protected:
	Node *nextPtr;// next pointer of Node
	Node *prevPtr;// previous pointer of Node	

	string symbol;// name of the stock
	int numOfShares;// number of shares
	double price;// the price of buy or sell
				 //double totalMoney;// the total money
};

// doubly linked the list and the StockAccount class
class StockAccount :public Account
{
public:
	StockAccount();// constructor
	~StockAccount();// destructor

					// Doubly linked list
	void insert(string &, int, double);//insert node
	void remove(Node *);//remove node
						// sort the list by two methods: bubble and selection
						// This is strategy design patterm
	void sortList();// sort the list
	void bubbleSort();// bubble sort
	void selectionSort();// selection sort
	double findPriceFromTXT(string &);// find the price of stock randomly in result1.txt or result2.txt file

	void displayPrice(string &);// display total price
	void displayCurrentPortfolio();// display current portfolio
	void buyShare(string &, int, double);// buy shares
	void sellShare(string &, int, double);// sell shares
	virtual void printHistory();// print transaction history
	void updateFiles();// save the current information				   
	void viewGraph();// matlab

private:
	double totalPortfolioValue;
	Node *myHead;// the head of the list 
	Node *myTail;// the tail of the list 
	int mySize;// the size of the list

};
#endif