//AUTHOR:	Dan Crisp
//DATE:		27OCT2016
//FILE:		parseSet.cpp
/* Readin and writing data from a text file. */
/* Works well for AllAlarmChannels.txt as input, but doens't handle saveset.txt header very well */
/* Skip spaces. This would only work for spaces at beginning of line. strtok and delimiter below do a much better job.
			Removed from get_stuff()
	while(fin.peek()== ' '){ //skip spaces
		fin.get(character);
		cout << "\nFOUND SPACE: '" << character << "'\n";
}*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

const int MAX_CHARS_PER_LINE = 100;
const int MAX_LINES_PER_FILE = 200;
const char* DELIMITER = " #";

void get_stuff( istream& , string* , string* , string* , string* , int );
void put_stuff( ostream& , string* , string* , string* , string* , int );

int main()
{
	system("cls");
	string name_set[MAX_LINES_PER_FILE] = {""};
	string value_set[MAX_LINES_PER_FILE] = {""};
	string name_read[MAX_LINES_PER_FILE] = {""};
	string value_read[MAX_LINES_PER_FILE] = {""};

	char inpfile[40] = {""};
	char outfile[40] = {""};
	
	char sortOption;
	
	// Request Filenames From User
	cout << "Enter filename for input relative to current location:\n";
	cin >> inpfile;
	cout << "Now enter filename for output:\n";
	cin >> outfile;
	
	
	//fin.open("AllAlarmChannels.txt");
	ifstream fin;
	fin.open(inpfile);
	if (!fin.good())
		return 1;
	
	cout << "\nGETTING INPUT:\n";
	for (int i = 0; i<MAX_LINES_PER_FILE; i++) {
		cout << i;
		get_stuff(fin, name_set, value_set, name_read, value_read, i);
		cout << "\n";
	}
	
	fin.close();
	
	
	ofstream fout;
	fout.open(outfile);
	if(!fout.good())
		return 1;
	
	cout << "\nWRITING OUTPUT:\n";
	for (int i = 0; i < MAX_LINES_PER_FILE; i++) {
		put_stuff(fout, name_set, value_set, name_read, value_read, i);
	}
	fout.close();
	
	//cout << "\nWould you like to sort these lines by RD value?\n";
	//cin >> sortOption;
	
	
	
	
	return 0;
}


void get_stuff(istream& fin, string* name_set, string* value_set, string* name_read, string* value_read, int i)
{
	char character;
	char* thing = new char[MAX_CHARS_PER_LINE];
	char * splitThing;
	int count = 0;
	
	// Skip lines starting with '#'
	while (fin.peek()=='#') {
		fin.getline(thing,MAX_CHARS_PER_LINE);
	}
	
	//getline(c-string, numchars )
	fin.getline(thing,MAX_CHARS_PER_LINE);
	//strtok().. if a token is found, a pointer to the beginning of token, otherwise a null pointer. Calling with NULL instead of c-str causes function to continue scanning where a previous successful call to the function ended.
	splitThing = strtok (thing,DELIMITER);
	while (splitThing != NULL) {
		switch(count) {
			case 0:
				name_set[i] = splitThing;
				splitThing = strtok (NULL, DELIMITER);
			case 1:
				value_set[i]= splitThing;
				splitThing = strtok (NULL, DELIMITER);
			case 2:
				name_read[i] = splitThing;
				splitThing = strtok (NULL, DELIMITER);
			case 3:
				value_read[i] = splitThing;
				splitThing = strtok (NULL, DELIMITER);
		}
		
		count++;
	}
}

void put_stuff(ostream& fout, string* name_set, string* value_set, string* name_read, string* value_read, int i)
{
	char *namestr = new char[name_set[i].length() + 1];
	char *valuestr = new char[value_set[i].length() + 1];
	char *namestr2 = new char[name_read[i].length() + 1];
	char *valuestr2 = new char[value_read[i].length() + 1];
	
	strcpy(namestr, name_set[i].c_str());
	strcpy(valuestr, value_set[i].c_str());
	strcpy(namestr2, name_read[i].c_str());
	strcpy(valuestr2, value_read[i].c_str());
	
	// Display output to fout and screen
	//		can't cout type string*, had to copy into char first.
	fout << i << " (" << namestr << ",  " << valuestr << ",  " << namestr2 << ",  " << valuestr2 << ")\n";
	cout << i << " (" << namestr << ",  " << valuestr << ",  " << namestr2 << ",  " << valuestr2 << ")\n";
}