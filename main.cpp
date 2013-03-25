#include <iostream>
#include <ctype.h>
#include <stdio.h>

using namespace std;
bool startHere();
void dispHelp();
void signIn();
void signOut();
//void signAllOut();
//string getAlias(string name);


int main () {
	while (1)
		if (startHere()) return 0;
	return 1;
}

bool startHere() {
	string mode;
	cout << ": ";
	cin >> mode;
	
	//cout << endl;
	switch (tolower(mode[0])) {
		case 'i': signIn(); break;
		case 'o': signOut(); break;
		//case 'e': signAllOut(); return true; break;
		default:  dispHelp(); break;
	}
	return false;
}

void dispHelp() {
	cout << "Sign In: i name" << endl;
	cout << "Sign Out: o name [work_peformed]" << endl;
	//cout << "Alias: a record_name alias_name" << endl;
	//cout << "Exit: e password" << endl;
}

void signIn() {
	string name;
	cin >> name;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	//name = getAlias(name);
	cout << name << " has logged in at " /*<< time*/ << "." << endl;
}

void signOut() {
	string name;
	cin >> name;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	//name = getAlias(name);
	cout << name << " has logged out at " /*<< time*/ << " spending " /*<< timeSpent*/ << " minutes." << endl;
}

/*void signAllOut() {
	string name;
	cin >> name;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
}*/

/*string getAlias(string name) {
	return name;
}*/
