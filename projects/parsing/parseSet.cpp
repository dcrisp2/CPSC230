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

void get_stuff( istream& , string* , string* , int );
char* put_stuff( ostream& , string* , string* , int );

int main()
{
	system("cls");
	string name[MAX_LINES_PER_FILE] = {""};
	string value[MAX_LINES_PER_FILE] = {""};

	char inpfile[40] = {""};
	char outfile[40] = {""};
	
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
		get_stuff(fin, name, value, i);
		cout << "\n";
	}
	
	fin.close();
	
	
	ofstream fout;
	fout.open(outfile);
	if(!fout.good())
		return 1;
	
	cout << "\nWRITING OUTPUT:\n";
	for (int i = 0; i < MAX_LINES_PER_FILE; i++) {
		put_stuff(fout, name, value, i);
	}
	fout.close();
	
	
	
	
	return 0;
}


void get_stuff(istream& fin, string* name, string* value, int i)
{
	char character;
	char* thing1 = new char[MAX_CHARS_PER_LINE];
	char * splitThing1;
	int count = 0;
	
	// Skip lines starting with '#'
	while (fin.peek()=='#') {
		fin.getline(thing1,MAX_CHARS_PER_LINE);
	}
	
	//getline(c-string, numchars )
	fin.getline(thing1,MAX_CHARS_PER_LINE);
	//strtok().. if a token is found, a pointer to the beginning of token, otherwise a null pointer. Calling with NULL instead of c-str causes function to continue scanning where a previous successful call to the function ended.
	splitThing1 = strtok (thing1,DELIMITER);
	while (splitThing1 != NULL) {
		if (!count){
			name[i] = splitThing1;
			splitThing1 = strtok (NULL, DELIMITER);
		} else if (count) {
			value[i]= splitThing1;
			splitThing1 = strtok (NULL, DELIMITER);
		}
		count++;
	}
	//name[i] = thing1;
	
	//return thing1;
}

char* put_stuff(ostream& fout, string* name, string* value, int i)
{
	
	char *namestr = new char[name[i].length() + 1];
	char *valuestr = new char[value[i].length() + 1];
		
	strcpy(namestr, name[i].c_str());
	strcpy(valuestr, value[i].c_str());
	
	// Display output to fout and screen
	//		can't cout type string*, had to copy into char first.
	fout << "caput " << namestr << "\t" << valuestr << "\n";
	cout << "caput " << namestr << "\t" << valuestr << "\n";
	
	return namestr;
}