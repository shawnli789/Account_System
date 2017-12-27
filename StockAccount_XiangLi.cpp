#define _CRT_SECURE_NO_WARNINGS

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>

#include<iostream>
#include<iomanip>
#include<time.h>
#include<ctime>
#include<fstream>
#include<sstream>
#include <cstdlib>
#include<stdlib.h>
#include "StockAccount_XiangLi.h"

#pragma comment(lib,"libmx.lib")
#pragma comment(lib,"libmex.lib")
#pragma comment(lib,"libeng.lib")

using namespace std;

// Node constructor
Node::Node(string &name, int num, double p)
	:symbol(name), numOfShares(num), price(p)
{
	this->nextPtr = 0;
	this->prevPtr = 0;
	//totalMoney = num * p;
}

// StockAccount constructor: read the current stock account information
StockAccount::StockAccount()
	:Account()
{
	// doubly linkedlist
	mySize = 0;
	myHead = 0;
	myTail = 0;

	// read information
	ifstream portfolioFile("Portfolio.txt", ios::in);
	if (!portfolioFile.is_open())// if the file is not open
	{
		ofstream newPortfolio("Portfolio.txt");
	}
	string name;
	int num;
	double price;
	while (portfolioFile >> name >> num >> price)// read the value from the file
	{
		Node *currentPtr = new Node(name, num, price);// creat a new node
		if (mySize == 0)
		{
			myHead = myTail = currentPtr;
		}
		else
		{
			currentPtr->prevPtr = myTail;
			myTail->nextPtr = currentPtr;
			myTail = currentPtr;// insert the node in the tail of the list
		}
		mySize++;
	}
	portfolioFile.close();
}

// destructor: delete all the nodes
StockAccount::~StockAccount()
{
	if (mySize != 0)// if there is node inside the list
	{
		Node *currentPtr;
		Node *tempPtr;
		currentPtr = myHead;

		while (currentPtr != 0)
		{
			tempPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
			delete tempPtr;
			--mySize;
		}
	}
}

// insert a new Node
void StockAccount::insert(string &name, int num, double p)
{
	Node *new_Node = new Node(name, num, p);// creat a new Node
	if (mySize == 0)// if the list is empty
	{
		myHead = new_Node;
		myTail = new_Node;
	}
	else// if not empty, insert the new Node at the end
	{
		new_Node->prevPtr = myTail;
		myTail->nextPtr = new_Node;
		myTail = new_Node;
		myTail->nextPtr = 0;
	}
	mySize++;// insert complete
}

// remove a Node in the list
void StockAccount::remove(Node *temp)
{
	if (myHead == myTail)
		myHead = myTail = 0;
	else
	{// if the Node you want to remove is the head of the list
		if (temp == myHead)
		{
			temp->nextPtr->prevPtr = 0;
			myHead = temp->nextPtr;
		}

		// if the Node you want to remove is the tail of the list
		else if (temp = myTail)
		{
			temp->prevPtr->nextPtr = 0;
			myTail = temp->prevPtr;
		}

		// the common situation
		else
		{
			temp->prevPtr->nextPtr = temp->nextPtr;
			temp->nextPtr->prevPtr = temp->prevPtr;
		}

		delete temp;// delete the temp Node
	}
	mySize--;
}

// sort the list
void StockAccount::sortList()
{
	srand((unsigned int)time(0));
	int choice = rand() % 2 + 1;
	if (choice == 1)
		bubbleSort();
	else if (choice == 2)
		selectionSort();
}

// sort the list of nodes by using bubble sort
void StockAccount::bubbleSort()
{
	cout << " (Bubble Sort Strategy is being used.)" << endl;
	// if the list is not empty or only one node
	if (mySize != 0)
	{
		Node *currentPtr = myHead;
		Node *temp = 0, *currentPrev = 0;
		double total1, total2;
		int sorted = 0;// check if it needs to be sorted

		for (int i = 0; i < mySize; i++)
		{
			while (currentPtr->nextPtr != 0)
			{
				temp = currentPtr->nextPtr;
				total1 = (currentPtr->numOfShares) * (currentPtr->price);
				total2 = (temp->numOfShares) * (temp->price);
				if (total1 < total2)// if the current total price is lower than temp, swap
				{
					sorted = 1;
					currentPtr->nextPtr = temp->nextPtr;
					temp->nextPtr = currentPtr;

					if (currentPrev != 0)// if current is not the first
						currentPrev->nextPtr = temp;
					currentPrev = temp;
					if (myHead == currentPtr)// if current is the head of the list
						myHead = temp;
					if (currentPtr->nextPtr == 0)// if current is the tail of the list
						myTail = currentPtr;
				}
				else
				{
					currentPrev = currentPtr;
					currentPtr = currentPtr->nextPtr;
				}
			}

			if (sorted == 0)
				break;
			else
			{
				currentPrev = 0;
				currentPtr = myHead;
				sorted = 1;
			}
		}
	}
}

// sort the list of nodes by using selection sort
void StockAccount::selectionSort()
{
	cout << "(Selection Sort Strategy is being used.)" << endl;
	Node *currentPtr = myHead;
	if (currentPtr == 0 || currentPtr->nextPtr == 0)// if there is no Node or only one node, there is no need to Sort
		return;

	Node * tempPtr = myHead->nextPtr;
	int number;
	double price;
	string name;
	int i = 0;
	int j = 0;
	double total1, total2;

	while (i < mySize - 1)
	{
		j = 0;
		tempPtr = currentPtr->nextPtr;
		while (j < mySize - 1 - i)
		{
			total1 = (currentPtr->numOfShares) * (currentPtr->price);
			total2 = (tempPtr->numOfShares) * (tempPtr->price);
			if (total2 > total1)
			{
				number = tempPtr->numOfShares;
				tempPtr->numOfShares = currentPtr->numOfShares;
				currentPtr->numOfShares = number;

				name = tempPtr->symbol;
				tempPtr->symbol = currentPtr->symbol;
				currentPtr->symbol = name;

				price = tempPtr->price;
				tempPtr->price = currentPtr->price;
				currentPtr->price = price;
			}
			tempPtr = tempPtr->nextPtr;
			j++;
		}
		currentPtr = currentPtr->nextPtr;
		i++;
	}
}

//find the price of the stock and return it
double StockAccount::findPriceFromTXT(string &name)
{
	string symbol_, date;
	double price;
	//randomly choose one file to open
	srand((unsigned int)time(0));
	int choice = rand() % 2 + 1;// the choice can be 1 or 2

	if (choice == 1)// open Re Result1.txt
	{
		ifstream file("Result_1.txt", ios::in);
		if (!file.is_open())
		{
			exit(1);// stock not found
		}
		else
		{
			while (file >> symbol_ >> price >> date)
			{
				if (name == symbol_)
					return price;
			}
		}
	}

	else// open Re Result2.txt
	{
		ifstream file("Result_2.txt", ios::in);
		if (!file.is_open())
		{
			exit(1);// stock not found
		}
		else
		{
			while (file >> symbol_ >> price >> date)
			{
				if (name == symbol_)
					return price;
			}
		}
	}
	return -1.0;
}

// display the total price
void StockAccount::displayPrice(string &name)
{
	double p = findPriceFromTXT(name);// find price from the stock name
	if (p == -1)
		cout << "The stock is not found." << endl;
	else
	{
		cout << "Company-Symbol" << "\t" << "Price per share" << endl;
		cout << name << "\t\t$" << p << endl;
	}
}

// display display current portfolio
void StockAccount::displayCurrentPortfolio()
{
	// read cash balance
	ifstream cash("Cash_Balance.txt");// read from before
	cash >> Account::cashBalance;
	cash.close();

	cout << "Cash balance = $" << Account::cashBalance << endl;// output the cash balance

	Node *currentPtr = myHead;// creat current pointer
	totalPortfolioValue = Account::cashBalance;// initialize the total portfolio value
	double totalMoney, price;

	if (mySize == 0)// when there is no stock in the account
		cout << "You don't have any shares of stock in your StockAccount." << endl;

	else
	{
		cout << left << setw(19) << "Company-Symbol" << setw(11) << "Number" << setw(20) << "Price-Per-Share" << setw(12) << "Total value" << endl;
		while (currentPtr != 0)// when current pointer doesn't point to 0
		{
			price = findPriceFromTXT(currentPtr->symbol);// find price from txt file

														 // calculate the total portfolio value
			totalMoney = price * currentPtr->numOfShares;
			totalPortfolioValue += totalMoney;

			cout << left << setw(19) << currentPtr->symbol << setw(11) << currentPtr->numOfShares
				<< "$" << setw(19) << price << "$" << setw(10) << totalMoney << endl;
			currentPtr = currentPtr->nextPtr;
		}
	}
	cout << "Total portfolio value: $" << totalPortfolioValue << endl;// output the total portfolio value
}

// but stock shares
void StockAccount::buyShare(string & name, int num, double max_price)
{
	double price = findPriceFromTXT(name);
	if (price == -1)// can not find the stock
		cout << "The stock is not found." << endl;

	else if (price > max_price)// if the price is higher than users want to pay
		cout << "The transaction failed, because the price of the stock is higher than the maximum price you want to pay." << endl;

	else// proceed buy shares
	{
		// read cash balance
		ifstream cash("Cash_Balance.txt");// read from before
		cash >> Account::cashBalance;
		cash.close();

		double totalMoney = num * price;
		if (totalMoney > Account::cashBalance)// if money is not enough
			cout << "The transaction failed, because your cash balance is not enough." << endl;
		else
		{
			Account::cashBalance -= totalMoney;// add to cash balance
			Node *currentPtr = myHead;
			while (currentPtr != 0 && currentPtr->symbol != name)// check if user already got the stock
				currentPtr = currentPtr->nextPtr;

			if (currentPtr != 0)// if the user already go the stock
			{
				currentPtr->numOfShares += num;
				currentPtr->price = price;
			}
			else// if not
				insert(name, num, max_price);
			cout << "You have purchased " << num << " shares of " << name << " at $" << price << " each for a total of $" << totalMoney;

			// add to history
			ofstream stockHistory;
			stockHistory.open("Stock_Transaction_History.txt", ios::app);
			if (stockHistory.is_open())
			{
				// get local time
				time_t t;
				struct tm * timeinfo;
				time(&t);
				timeinfo = localtime(&t);
				stockHistory << "Buy\t" << name << "\t" << num << "\t" << price << "\t" << totalMoney << "\t"
					<< timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << endl;
				stockHistory.close();
			}
			else
				cout << "Unable to open Stock_Transaction_History.txt" << endl;

			//int sort;// choice a sort method
			//cout << "Please chose a sort method." << endl;
			//cout << "1. Bubble sort." << endl;
			//cout << "2. Selection sort." << endl;
			//cin >> sort;
			//sortList(sort);
			sortList();

			updateFiles();// update stock to txt
			ofstream cashBalance("Cash_Balance.txt");
			cashBalance << Account::cashBalance << endl;// update the file of cash balance
			cashBalance.close();
		}
	}
}

// sell stock shares
void StockAccount::sellShare(string &name, int num, double min_price)
{
	double price = findPriceFromTXT(name);
	if (price == -1)// can not find the stock
		cout << "The stock is not found." << endl;
	else if (price < min_price)// if the price is lower than users want to sell
		cout << "The transaction failed, because the price of the stock is lower than the minimum price you want to sell." << endl;
	else// proceed sell shares
	{
		// read cash balance
		ifstream cash("Cash_Balance.txt");// read from before
		cash >> Account::cashBalance;
		cash.close();

		Node *currentPtr = myHead;
		while (currentPtr != 0 && currentPtr->symbol != name)
			currentPtr = currentPtr->nextPtr;

		if (currentPtr->numOfShares < num)// if the shares are not enough
			cout << "The transaction failed, because the amount of shares of the stock are not enough." << endl;
		else
		{
			double totalMoney = num * price;
			Account::cashBalance += totalMoney;
			currentPtr->numOfShares -= num;
			currentPtr->price = price;

			if (currentPtr->numOfShares == 0)
				remove(currentPtr);

			cout << "You have sold " << num << " shares of " << name << " at $" << price << " each for a total of $" << totalMoney;

			// add to history
			ofstream stockHistory;
			stockHistory.open("Stock_Transaction_History.txt", ios::app);
			if (stockHistory.is_open())
			{
				// get local time
				time_t t;
				struct tm * timeinfo;
				time(&t);
				timeinfo = localtime(&t);
				stockHistory << "Sell\t" << name << "\t" << num << "\t" << price << "\t" << totalMoney << "\t"
					<< timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << endl;
				stockHistory.close();
			}
			else
				cout << "Unable to open Stock_Transaction_History.txt" << endl;

			//int sort;// choice a sort method
			//cout << "Please chose a sort method." << endl;
			//cout << "1. Bubble sort." << endl;
			//cout << "2. Selection sort." << endl;
			//cin >> sort;
			//sortList(sort);
			sortList();

			updateFiles();// update stock to txt
			ofstream cashBalance("Cash_Balance.txt");
			cashBalance << Account::cashBalance << endl;// update the file of cash balance
			cashBalance.close();
		}
	}
}

// print tansaction history
void StockAccount::printHistory()
{
	ifstream History("Stock_Transaction_History.txt");// open file to read
	string events, stock, time;
	double pricePerShare, totalValue, number;

	if (History.is_open())
	{
		cout << left << setw(10) << "Event" << setw(18) << "CompanySymbol" << setw(11) << "Number" << setw(18) << "PricePerShare"
			<< setw(15) << "TotalValue" << setw(5) << "Time" << endl;
		while (History >> events >> stock >> number >> pricePerShare >> totalValue >> time)// read the information
		{
			cout << left << setw(10) << events << setw(18) << stock << setw(11) << number
				<< "$" << setw(17) << pricePerShare << "$" << setw(14) << totalValue << setw(12) << time << endl;
		}
		History.close();
	}
	else
		cout << "Unable to open the stock history." << endl;
}

// update files
void StockAccount::updateFiles()
{
	time_t t;
	struct tm * timeinfo;
	time(&t);
	timeinfo = localtime(&t);

	Node* currentPtr = myHead;
	ofstream portfolioFile;
	portfolioFile.open("Portfolio.txt");
	double price, totalPrice;
	double totalPort = Account::cashBalance;;

	while (currentPtr != 0)
	{
		price = findPriceFromTXT(currentPtr->symbol);
		totalPrice = price*(currentPtr->numOfShares);
		totalPort += totalPrice;
		portfolioFile << currentPtr->symbol << "\t" << currentPtr->numOfShares << "\t" << price << endl;
		currentPtr = currentPtr->nextPtr;// move to the next node
	}
	portfolioFile.close();

	// matlab update
	ofstream matlab("Totalvalue.txt", ios::app);
	matlab << left << setw(10) << (timeinfo->tm_year) + 1900 << setw(7) << (timeinfo->tm_mon) + 1 << setw(7) << timeinfo->tm_mday << setw(7)
		<< timeinfo->tm_hour << setw(7) << timeinfo->tm_min << setw(7) << timeinfo->tm_sec << setw(7) << totalPort << endl;
	matlab.close();
}

// interface between c++ and matlab, print out graph
void StockAccount::viewGraph()
{
	Engine *ep;

	if (!((ep = engOpen(nullptr))))
	{
		cout << "Error: Not Found" << endl;
		exit(1);
	}

	engSetVisible(ep, false);

	int y, m, da, h, mi, s;
	double v;
	double a[10000][6];
	double b[10000];
	int size = 0;
	ifstream matlab("Totalvalue.txt", ios::in);
	if (!matlab)
	{
		cout << "File could not be opened." << endl;
		return;
	}
	while (matlab >> y >> m >> da >> h >> mi >> s >> v)// read the value of the file
	{
		a[size][0] = y;// year
		a[size][1] = m;// month
		a[size][2] = da;// day
		a[size][3] = h;// hour
		a[size][4] = mi;// minute
		a[size][5] = s;// second
		b[size] = v;// value
		size++;
	}
	if (mySize != 0)
	{
		mxArray *mx1;
		mxArray *mx2;
		mx1 = mxCreateDoubleMatrix(6, size, mxREAL);
		mx2 = mxCreateDoubleMatrix(1, size, mxREAL);
		memcpy((void *)mxGetPr(mx1), (void*)a, 6 * sizeof(double)*size);
		memcpy((void *)mxGetPr(mx2), (void*)b, sizeof(double)*size);
		engPutVariable(ep, "A", mx1);
		engPutVariable(ep, "B", mx2);

		engEvalString(ep, "X=A';");
		engEvalString(ep, "a=X(:,1);b=X(:,2);c =X(:,3);d=X(:,4);e=X(:,5);f=X(:,6);");//get 6 separate matrix
		engEvalString(ep, "x=datenum(a,b,c,d,e,f);");// get date number
		engEvalString(ep, "Y=B;");
		engEvalString(ep, "plot(x,Y,'-*');");// plot the graph
		engEvalString(ep, "ylim([6000 12000]);");
		engEvalString(ep, "datetick('x',0);");// place date number with time
		engEvalString(ep, "title('Plot of Total value of portfolio with time');");// title
		engEvalString(ep, "xlabel('Time'),ylabel('TotalValue');");// axis name

		engEvalString(ep, "pause(15.0);");// 15 seconds to close the window
		system("pause");
		engClose(ep);// close matlab engine
		return;
	}
	engClose(ep);// close matlab engine
	return;
}