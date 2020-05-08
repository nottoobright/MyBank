#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<iomanip>
#include "auth.h"
#include "bankaccount.h"
using namespace std;


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void loan_manage(int);
void check_credit(int);
void display_all();
void transact(int, int, int);
void deposit_withdraw(int, int);
int menu();

int main()
{
  auth user;
  int choice;
  cout<<"\n\n\t\t\t\t======================\n";
      cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
      cout<<"\n\t\t\t\t======================\n";

        cout<<"\t\t\t\t    ::AUTH::\n";
        cout<<"\n\t\t\t\t1. REGISTER";
        cout<<"\n\t\t\t\t2. LOGIN ";
        cin>>choice;
  if(choice == 1){
    string username, password;
    cout<<"\n\t\t\t\t1. SELECT A USERNAME: ";
    cin >> username;
    cout<<"\n\t\t\t\t1. SELECT A PASSWORD: ";
    cin >> password;
    ofstream file;

    file.open(username + ".txt");
    file << username << endl << password;
    file.close();
    system("CLS");
    main();
  }
  else if(choice == 2){
    if(user.isLoggedIn()){
      menu();
    }
    {
      cout << "Invalid details";
      return 0;
    }
  }

	return 0;
}

int menu()
{
    char choice;
	int num;
	int amt;
		cout << "Successfully logged in!";
    do
    {
      system("CLS");
      cout<<"\n\n\t\t\t\t======================\n";
      cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
      cout<<"\n\t\t\t\t======================\n";

        cout<<"\t\t\t\t    ::MAIN MENU::\n";
        cout<<"\n\t\t\t\t1. NEW ACCOUNT";
        cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
        cout<<"\n\t\t\t\t5. LOAN";
        cout<<"\n\t\t\t\t6. CHECK CREDIT RATING";
        cout<<"\n\t\t\t\t7. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\t\t\t\t8. SEND MONEY";
        cout<<"\n\t\t\t\t9. CLOSE AN ACCOUNT";
        cout<<"\n\t\t\t\tA. MODIFY AN ACCOUNT";
        cout<<"\n\t\t\t\tE. EXIT";
        cout<<"\n\n\t\t\t\tSelect Your Option: ";
        cin>>choice;

        switch(choice)
        {
        case '1':
          write_account();
          break;
        case '2':
          system("CLS");
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          deposit_withdraw(num, 1);
          break;
        case '3':
          system("CLS");
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          deposit_withdraw(num, 2);
          break;
        case '4':
          system("CLS");
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          display_sp(num);
          break;
        case '5':
            system("CLS");
            int op;
            cout<<"\n\n\t\t\t\t======================\n";
            cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
            cout<<"\n\t\t\t\t======================\n";

            cout<<"\t\t\t\t    ::LOAN PAYMENTS::\n";
            cout<<"\n\t\t\t\t1. NEW LOAN";
            cout<<"\n\t\t\t\t2. REPAY LOAN";
            cout<<"\n\n\t\t\t\tSelect Your Option: ";
            cin>>op;
            loan_manage(op);
            break;
        case '6':
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          check_credit(num);
          break;
        case '7':
            display_all();
            break;
        case '8':
          int num1;
          cout<<"\n\n\t\t\tEnter The account No of sender : ";cin>>num;
          cout<<"\n\n\t\t\tEnter The account No of receiver : ";cin>>num1;
          cout<<"\n\n\t\t\tEnter amount : ";cin>>amt;
          transact(num, num1, amt);
          break;
        case '9':
          system("CLS");
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          delete_account(num);
          break;
        case 'A':
          system("CLS");
          cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
          modify_account(num);
          break;
        case 'E':
          system("CLS");
          cout<<"\n\n\t\t\tBye";
          break;
        default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
      } while(choice!='10');
  return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}


void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.getaccnum()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}


void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.getaccnum()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.getaccnum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nRecord Deleted ..";
}

void loan_manage(int n)
{
    bool found=false;
    account ac;
    loan ln;
    int a;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    if(n == 1)
    {
        cout<<"\t\t\t\tEnter Account Number: ";
        cin>>a;
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.getaccnum()==a){
                ln.new_loan(n);
                int amount = ln.getamount();
                if(amount * 0.15 <= ac.getdeposit()){
                    if(ac.getrating() >= 5){
                        ac.dep(amount);
                        ac.set_loan(amount);
                        ac.setrating(ac.getrating() - 3);
                        cout << "\n\t\t\tLoan Approved ";
                        found = true;
                    }
                    else{
                        cout<<"\n\t\t\tYou are not eligible";
                        found = true;
                    }
                }
                else{
                    cout<<"\n\t\t\tYou are not eligible";
                    found = true;
                }
            }
        }
    }
    if(n == 2)
    {
        cout<<"\t\t\t\tEnter Account Number: ";
        cin>>a;
        while(!File.eof() && found==false)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));
            if(ac.getaccnum()==a){
                ln.new_loan(n);
                int payment = ln.getamount();
                int amount = ac.get_loan();
                if(amount == 0){
                    cout<<"\n\t\t\tYou have no remaining loan";
                    if(ac.getrating() < 5){
                        ac.setrating(ac.getrating() + 3);
                    }
                    found = true;
                    break;
                }
                if(ac.getdeposit() >= payment){
                    if(payment > amount){
                        payment = amount;
                        continue;
                    }
                    ac.draw(payment);
                    ac.set_loan(amount - payment);
                    ac.setrating(ac.getrating() + 1);
                    cout<<"\n\t\t\tRemaining Loan: " << ac.get_loan();
                    found = true;
                }
                else{
                    cout<<"\n\t\t\tInsufficient Balance";
                    found = true;
                }
            }
        }
    }
    int pos=(-1)*static_cast<int>(sizeof(ac));
    File.seekg(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
    File.close();
}

void check_credit(int n)
{
    bool found=false;
    account ac;
    int rating;
    char result;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.getaccnum()== n){
            rating = ac.getrating();
            if(rating > 8){
                result = 'A';
            }
            else if(rating <= 8 && rating > 6){
                result = 'B';
            }
            else if(rating >= 5){
                result = 'C';
            }
            else{
                result = 'D';
            }
            cout<<"\n\t\t\tYour credit rating is: " << result;
            cout<<"\n\t\t\tYou need at least C rating to get a loan";
            found = true;
        }
    }
}

void transact(int sender, int receiver, int amt)
{
    bool found = false;
    account ac;
    account bc;
    transaction t;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.getaccnum()==sender){
           ac.draw(amt);
		}
		File.read(reinterpret_cast<char *> (&bc), sizeof(account));
		if(bc.getaccnum()==receiver){
            bc.dep(amt);
		}
        t.record(sender, receiver, amt);
        t.record_transaction(t);
        found = true;
	}
    int pos=(-1)*static_cast<int>(sizeof(ac));
    int pos1=(-1)*static_cast<int>(sizeof(bc));
    File.seekg(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
    File.seekg(pos1,ios::cur);
    File.write(reinterpret_cast<char *> (&bc), sizeof(account));
	File.close();
}

void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.getaccnum()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSITS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.getdeposit()-amt;
				if(bal<0)
					cout<<"Insufficient balance";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t\t\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}

