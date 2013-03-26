#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <vector>

using namespace std;

void dispHelp();
void signIn();
void signOut();
//void signAllOut();
bool isIn(string name);

//string getAlias(string name);
bool startHere();
vector<string> inList;


int main () {
	cout << "\033[2J";
	while (1)
		if (startHere()) return 0;
	return 1;
}

bool startHere() {
	string mode;
	cout << "Ready: ";
	cin >> mode;

	//cout << endl;
	switch (tolower(mode[0])) {
		case 'i': signIn(); break;
		case 'o': signOut(); break;
		//case 'l': listIn(); break;
		//case 'e': signAllOut(); return true; break;
		default:  dispHelp(); break;
	}
	return false;
}

void dispHelp() {
	cout << "Sign In: i name" << endl;
	cout << "Sign Out: o name work_peformed" << endl;
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
	if (isIn(name)) {
		cout << "\033[;31m" << name << " is already signed in" << "\033[0m" << endl;
		return;
	}
	inList.push_back(name);


	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%Y-%m-%d@%R",timeinfo);

	cout << name << " signed in on " << buffer << "." << endl;
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

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%Y-%m-%d@%R",timeinfo);

	cout << name << " has logged out at " << buffer << " spending " /*<< timeSpent*/ << " minutes." << endl;
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

bool isIn(string name) {
	for(int i=0; i < inList.size(); i++)
		if (inList[i].compare(name) == 0)
			return true;
	return false;

}
