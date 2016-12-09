//AUTHOR:		DANIEL CRISP
//DATE:			7DEC2016
//DESC:			phonebook.cpp

#include<cstdlib>
#include<string>
#include<map>
#include<fstream>
#include<iostream>

using namespace std;

const char MAX_LINES_PER_FILE = 100;
const char MAX_CHARS_PER_LINE = 100;
const char* DELIMITER = ",";

void get_data(istream&, string*, string*, int );

int main()
{
	system("cls");
	
	string inputfile("phonebook.db");
	char * name = (char*) malloc (41);
	char ans;
	string names[MAX_LINES_PER_FILE] = {""};
	string numbers[MAX_LINES_PER_FILE] = {""};
	int num = 0;
	int i = 0;
	
	map <string, string> book;
	ifstream fin;
	
	fin.open(inputfile);
	if(!fin.good()) {
		cout << "That file is no good.";
		return 1;
	}
	
	cout << "\nGETTING ALIASMAP...\n";
	while (!fin.eof()) {
		get_data(fin, names, numbers, i);
		book[names[i]] = numbers[i]; //So a query using old name, retrieves a new one!
		i++;
	}
	num = i-1; //re-used for aliasmap data
	cout << "\tExiting phonebook.db. Non-null data of length " << num << "\n";
	fin.close();
	
	cout << "========================================";
	cout << "\nThis is your phonebook.\n\n";
	cout << "========================================";
	
	do {
	cout << "\n\nPlease enter a name of someone you'd like to contact:\n";
	
	char * name = (char*) malloc (41);
	cin >> name;
	
	if(book.find(name) != book.end()) {
		cout << "\n\n" << name << " can be contacted by using number " << book[name] << "\n\n";
	} else {
		cout << "\n\nYour phonebook does not have " << name << " in it.\n\n";
	}
	cout << "\nDo you want to continue? Enter either 'Y' or 'y' to continue.\n";
	cin >> ans;
	cout << "\n-----------------------------------------";
	} while ((ans == 'y') || (ans == 'Y'));
	
	cout << "\n\ngoodbye...\n";
	
	return 0;
}

void get_data(istream& fin, string* names, string* numbers, int i)
{	
	char* line = new char[MAX_CHARS_PER_LINE];
	char * strings;
	int count = 0;
	
	fin.getline(line,MAX_CHARS_PER_LINE);
	
	strings = strtok(line, DELIMITER);
	while (strings != NULL) {
		switch (count) {
			case 0:
				names[i] = strings;
				strings = strtok (NULL, DELIMITER);
			case 1:
				numbers[i] = strings;
				strings = strtok (NULL, DELIMITER);
		}
		count++;
	}
	delete [] line;
};
