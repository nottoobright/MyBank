#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class auth
{
    string username;
    string password;
public:
	bool isLoggedIn();
};

bool auth::isLoggedIn()
{
	string username, password, un, pw;

	cout << "Enter Username: ";
	cin >> username;
	cout << "Enter Password: ";
	cin >> password;

	ifstream read(username + ".txt");
	getline(read, un);
	getline(read, pw);

	if (un == username && pw == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}
