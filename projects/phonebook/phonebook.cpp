//AUTHOR:		DANIEL CRISP
//DATE:			7DEC2016
//DESC:			phonebook.cpp

#include<cstdlib>
#include<cstring>
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
	char input[50] = {""};
	string names[MAX_LINES_PER_FILE] = {""};
	string numbers[MAX_LINES_PER_FILE] = {""};
	int num = 0;
	int i = 0;
	
	map <string, string> numberMap;
	ifstream fin;
	
	fin.open(inputfile);
	if(!fin.good()) {
		cout << "That file is no good.";
		return 1;
	}
	
	cout << "\nGETTING ALIASMAP...\n";
	while (!fin.eof()) {
		get_data(fin, names, numbers, i);
		numberMap[names[i]] = numbers[i]; //So a query using old name, retrieves a new one!
		i++;
	}
	num = i-1; //re-used for aliasmap data
	cout << "\tExiting phonebook.db. Non-null data of length " << num << "\n";
	fin.close();
	
	cout << "This is your phonebook.\n\nPlease enter a name of someone you'd like to contact:\n";
	
	getline(cin,input);
	
	cout << "\n\n" << input << " can be contacted by using number " << numberMap[input];
	
	
	
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