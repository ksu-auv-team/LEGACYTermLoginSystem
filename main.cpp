#include <iostream>
#include <ctype.h>
#include <stdio.h>

using namespace std;
void startHere();
void dispHelp();
void signIn();
void signOut();

int main () {
	startHere();
	return 1;
}

void startHere() {
	string mode;
	string name;
	cout << ": ";
	cin >> mode >> name;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	cout << mode << endl;
	cout << name << endl;
	switch (tolower(mode[0])) {
		case 'h': dispHelp(); break;
		case 'e': signIn(/**/); break;
		case 'l': signOut(/**/); break;
	}
}

void dispHelp() {
	throw 1;
}

void signIn() {
	throw 1;
}

void signOut() {
	throw 1;
}
