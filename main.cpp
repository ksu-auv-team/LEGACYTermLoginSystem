#include <iostream>
#include <ctype.h>
#include <stdio.h>

using namespace std;
bool startHere();
void dispHelp();
void signIn();
void signOut();
void signAllOut();

int main () {
	while (1)
		if (startHere()) return 0;
	return 1;
}

bool startHere() {
	string mode;
	string name;
	cout << ": ";
	cin >> mode >> name;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	cout << endl;
	switch (tolower(mode[0])) {
		//case 'h': dispHelp(); break;
		case 'i': signIn(/**/); break;
		case 'o': signOut(/**/); break;
		case 'e': signAllOut(); return true; break;
		default:  dispHelp(); break;
	}
	return false;
}

void dispHelp() {
	cout << "Sign In: i name" << endl;
	cout << "Sign Out: o name [work_peformed]" << endl;
	cout << "Alias: a record_name alias_name" << endl;
	cout << "Exit: e password" << endl;
}

void signIn() {
	throw 1;
}

void signOut() {
	throw 1;
}

void signAllOut() {
	throw 1;
}
