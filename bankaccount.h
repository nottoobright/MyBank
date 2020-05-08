#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <vector>
using namespace std;

class transaction
{
    int sender;
    int receiver;
    int amount;
	vector<transaction> transactions;
public:
    void record(int, int, int);
    void record_transaction(transaction);
};

class account
{
	int accnum;
	char name[50];
	int deposit;
	int rating = 5;
	int loan;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void set_loan(int);
	void report() const;
	int getaccnum() const;
	int getrating() const;
	int setrating(int);
    int get_loan();
	int getdeposit() const;
	char gettype() const;
};

class loan : public account
{
    int amount;
    int interest;
public:
    void new_loan(int);
    int getamount();
};


void transaction::record(int n, int m, int amt)
{
    sender = n;
    receiver = m;
    amount = amt;
}

void loan::new_loan(int n)
{
    cout << "\n\t\t\tEnter the Amount: ";
    cin>>amount;
}

int loan::getamount()
{
    return amount;
}

void transaction::record_transaction(transaction t)
{
    transactions.push_back(t);
}

void account::set_loan(int n)
{
    loan = n;
}

int account::get_loan()
{
    return loan;
}

void account::create_account()
{
	//system("CLS");
	cout << "\n\t\t\tEnter the Account No. : ";
	cin >> accnum;
	cout << "\n\n\t\t\tEnter the Name of the Account holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\t\t\tEnter The Initial amount : ";
	cin >> deposit;
	cout << "\n\n\t\t\tAccount Created..";
}

void account::show_account() const
{
	cout << "\n\t\t\tAccount No. : " << accnum;
	cout << "\n\t\t\tAccount Holder Name : ";
	cout << name;
	cout << "\n\t\t\tBalance amount : " << deposit;
}


void account::modify()
{
	cout << "\n\t\t\tAccount No. : " << accnum;
	cout << "\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\t\t\tModify Type of Account : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\t\t\tModify Balance amount : ";
	cin >> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << accnum << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::getaccnum() const
{
	return accnum;
}

int account::getrating() const
{
    return rating;
}

int account::setrating(int n)
{
    rating = n;
}

int account::getdeposit() const
{
	return deposit;
}

char account::gettype() const
{
	return type;
}
