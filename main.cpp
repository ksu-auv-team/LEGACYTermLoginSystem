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

	try {
		switch (tolower(mode[0])) {
			case 'i': signIn(); break;
			case 'o': signOut(); break;
			case 'l': listIn(); break;
			//case 'e': signAllOut(); return true; break;
		}
	} catch (const out_of_range& oor) {
		cout << "\033[;31mError\033[0m" << endl;
	}
	return false;
}

void dispHelp() {
	cout << "\033[0;33mSign In: i name" << endl;
	cout << "Sign Out: o name work_peformed" << endl;
	cout << "List Users In: l\033[0m" << endl;
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

void listIn() {
	if (inList.size() == 0)
		cout << "\033[;31mLab is empty.\033[0m" << endl;
	cout << "\033[;36m";
	for(int i=0; i < inList.size(); i++)
		cout << inList[i] << endl;
	cout << "\033[0m" << endl;
}


