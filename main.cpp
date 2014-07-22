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
void printlnError(string msg);
void printlnBlue(string msg);

//string getAlias(string name);
bool startHere();
vector<string> inList;
vector<string> parkingList;
bool passList[10];
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
        printlnError("Error");
    }
    return false;
}

void dispHelp() {
    cout << "\033[0;33m";
    cout << "Sign In: i name" << endl;
    cout << "Sign Out: o name work_peformed" << endl;
    cout << "List Users In: l" << endl;
    cout << "Get Parking Pass: p g last_digit name" << endl;
    cout << "Return Parking Pass: p r last_digit name" << endl;
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
        printlnError(name + " is already signed in");
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

    printlnBlue(name + " signed in on " + buffer);
    
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
        printlnError(name + " is already signed out");
        return;
    }
    if (isParking(name)) {
        printlnError("You must return the pass first!");
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

    printlnBlue(name + " has logged out at " + buffer + " spending " + to_string(minIn) + " minutes. Working on " + work);
}

bool isIn(string name) {
    for(int i=0; i < inList.size(); i++)
        if (inList[i].compare(name) == 0)
            return true;
    return false;
}

void listIn() {
    if (inList.size() == 0) {
        printlnError("Lab is empty.");
        return;
    }
    cout << "\033[;36m";
    for(int i=0; i < inList.size(); i++)
        cout << inList[i] << endl;
    cout << "\033[0m" << endl;
}

void parking() {
    string action, numberS, name;
    cin >> action;
    cin >> numberS;
    cin >> name;

    int number;
    try {
        number = std::stoi(numberS);
    } catch (...) {
        printlnError("Can not read pass number");
        return;
    }

    if (!(number == 0 || number == 7 || number == 8 || number == 9)) {
        printlnError("Invalid pass number");
        return;
    }


    const int length = name.length();
    for(int i=0; i < length; i++)
    {
        name[i] = tolower(name[i]);
    }
    //name = getAlias(name);
    if (!isIn(name)) {
        printlnError(name + ", you must be signed in to use parking passes!");
        return;
    }

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%Y-%m-%d@%R",timeinfo);

    if (tolower(action[0]) == 'g') {
        if (passList[number]) {
            printlnError("Pass is already out.");
            return;
        }
        printlnBlue(name + " took a parking pass on " + buffer);
        parkingList.push_back(name);
        passList[number] = true;
    } else if (tolower(action[0]) == 'r') {
        printlnBlue(name + " returned a parking pass on " + buffer);
        int listPos = 0;
        for(int i=0; i < parkingList.size(); i++)
            if (parkingList[i].compare(name) == 0) {
                parkingList.erase(parkingList.begin()+i);
                listPos = i;
            }
        passList[number] = false;
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

void printlnError(string msg) {
    cout << "\a\a\a\033[;31m" << msg << "\033[0m" << endl;
}

void printlnBlue(string msg) {
    cout << "\033[;36m" << msg << "\033[0m" << endl;
}