/*
This main.cpp is part of TermLoginSystem.

TermLoginSystem is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

TermLoginSystem is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with TermLoginSystem.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <iomanip>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <limits>
#include <stdexcept> 

using namespace std;

void dispHelp();
void signIn();
void signOut();
void listIn();
bool isIn(string name);
void parking();
bool isParking(string name);

//string getAlias(string name);
bool startHere();
vector<string> inList;
vector<string> parkingList;
vector<time_t> inTime;


int main () {
	cout << "\033[2J";
	while (1)
		if (startHere()) return 0;
	return 1;
}

bool startHere() {
	//dispHelp();
	cout << endl;
	string mode;
	cout << "\033[;32mReady: \033[0m";
	cin >> mode;

	try {
		switch (tolower(mode[0])) {
			case 'i': signIn(); break;
			case 'o': signOut(); break;
			case 'l': listIn(); break;
			case 'p': parking(); break;
			default: dispHelp(); break;
		}
	} catch (const out_of_range& oor) {
		cout << "\033[;31mError\033[0m" << endl;
	}
	return false;
}

void dispHelp() {
	cout << "\033[0;33mSign In: i name" << endl;
	cout << "Sign Out: o name work_peformed" << endl;
	cout << "List Users In: l" << endl;
	cout << "Parking Pass: p i/o last_digit name" << endl;
	cout << "\033[0m";
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

	cout << "\033[;36m" << name << " signed in on " << buffer << ".\033[0m" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void signOut() {
	string name, work;
	char cwork[256];
	cin >> name;
	cin >> work;
	cin.getline(cwork, 256);
	work += cwork;
	//work = work.substr(1);
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
	if (isParking(name)) {
		cout << "\033[;31m" << "You must return the pass first!" << "\033[0m" << endl;
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

	double hoursIn= ((double)minIn/60.0);

	myfile.open(fname.c_str(), ios::app | ios::out);
	myfile << buffer << "," << minIn << "," ;
	myfile << hoursIn << "," << setprecision(2) << fixed << work ;
	myfile << endl;
	myfile.close();

	cout << "\033[;36m" << name << " has logged out at " << buffer << " spending " << minIn << " minutes.\033[0m " << work << endl;
}

bool isIn(string name) {
	for(int i=0; i < inList.size(); i++)
		if (inList[i].compare(name) == 0)
			return true;
	return false;
}

void listIn() {
	if (inList.size() == 0)
		cout << "\033[;31mLab is empty.\033[0m" << endl;
	cout << "\033[;36m";
	for(int i=0; i < inList.size(); i++)
		cout << inList[i] << endl;
	cout << "\033[0m" << endl;
}

void parking() {
	string action, number, name;
	cin >> action;
	cin >> number;
	cin >> name;

	const int length = name.length();
	for(int i=0; i < length; i++)
	{
		name[i] = tolower(name[i]);
	}
	//name = getAlias(name);
	if (!isIn(name)) {
		cout << "\033[;31m"<< name << ", you must be signed in to use parking passes!\033[0m" << endl;
		return;
	}

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%Y-%m-%d@%R",timeinfo);

	if (tolower(action[0]) == 'o') {
		cout << "\033[;36m" << name << " took a parking pass on " << buffer << ".\033[0m" << endl;
		parkingList.push_back(name);
	} else if (tolower(action[0]) == 'i') {
		cout << "\033[;36m" << name << " returned a parking pass on " << buffer << ".\033[0m" << endl;
		int listPos = 0;
		for(int i=0; i < parkingList.size(); i++)
			if (parkingList[i].compare(name) == 0) {
				parkingList.erase(parkingList.begin()+i);
				listPos = i;
			}
	} else {
		dispHelp();
	}
}

bool isParking(string name) {
	for(int i=0; i < parkingList.size(); i++)
		if (parkingList[i].compare(name) == 0)
			return true;
	return false;
}