#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <fstream>

using namespace std;

void dispHelp();
void signIn();
void signOut();
//void signAllOut();
bool isIn(string name);

//string getAlias(string name);
bool startHere();
vector<string> inList;
vector<time_t> inTime;


int main () {
	cout << "\033[2J";
	while (1)
		if (startHere()) return 0;
	return 1;
}

bool startHere() {
	dispHelp();
	cout << endl;
	string mode;
	cout << "\033[;32mReady: \033[0m";
	cin >> mode;

	//cout << endl;
	switch (tolower(mode[0])) {
		case 'i': signIn(); break;
		case 'o': signOut(); break;
		//case 'l': listIn(); break;
		//case 'e': signAllOut(); return true; break;
	}
	return false;
}

void dispHelp() {
	cout << "\033[0;33mSign In: i name" << endl;
	cout << "Sign Out: o name work_peformed\033[0m" << endl;
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

	inTime.push_back(rawtime);

	ofstream myfile;
	string fname = name + ".timelog";
	myfile.open(fname.c_str(), ios::app | ios::out);
	myfile << buffer << ",";
	myfile.close();

	cout << name << " signed in on " << buffer << "." << endl;
}

void signOut() {
	string name, work;
	cin >> name;
	cin >> work;
	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	//name = getAlias(name);
	if (!isIn(name)) {
		cout << "\033[;31m" << name << " is already signed out" << "\033[0m" << endl;
		return;
	}

	int listPos = 0;
	for(int i=0; i < inList.size(); i++)
		if (inList[i].compare(name) == 0) {
			inList.erase(inList.begin()+i);
			listPos = i;
		}

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%Y-%m-%d@%R",timeinfo);

	int minIn = difftime(rawtime, inTime[listPos]) / 60;
	inTime.erase(inTime.begin()+listPos);

	minIn++;

	ofstream myfile;
	string fname = name + ".timelog";
	myfile.open(fname.c_str(), ios::app | ios::out);
	myfile << buffer << "," << minIn << "," << work << endl;
	myfile.close();

	cout << name << " has logged out at " << buffer << " spending " << minIn << " minutes." << endl;


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
