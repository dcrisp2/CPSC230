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
void fill_index( int index[]); //Are we sure we actually need to be as specific as to say 'index[]'?
void bubblesort( string val[], int index[], int MAX_LINES_PER_FILE);
char *request_filename(string);
//char request_filename(string);

int main()
{
	system("cls");
	string name_set[MAX_LINES_PER_FILE] = {""};
	string value_set[MAX_LINES_PER_FILE] = {""};
	string name_read[MAX_LINES_PER_FILE] = {""};
	string value_read[MAX_LINES_PER_FILE] = {""};

	//char inpfile[40] = {""};
	char inpfile[40] = {""};
	//char outfile[40] = {""};
	char outfile[40] = {""};
	
	char sortOption;
	int index[MAX_LINES_PER_FILE];
	fill_index(index);
	
	// Request Filenames From User
	//char *inpfile = request_filename("Enter input filename:\n"); //Worked, but wanted to use non-pointed char array
	//inpfile = request_filename("Enter input filename:\n"); //Cannot assign to char[40]
	strcpy(inpfile,request_filename("Enter saveset filename:\n"));
	strcpy(outfile,request_filename("Enter output filename for verifying resulting array values:\n"));
	
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
	
	
	/* Having acquired values from saveset and printing them out for verification...
		Create arrays from aliasmap.
			This filename can be considered static.
			But it's length and values may change as necessary.
	*/
	// Ask user to enter filename for printing values retrieved from saveset
	strcpy(outfile,request_filename("Enter output filename for translated saveset:\n"));
	
	strcpy(outfile,request_filename("Enter :\n"));
	

	
	
	return 0;
}

/*------------------------------------------------------------------------------
Function definitions below...
--------------------------------------------------------------------------------*/
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
	//strtok().. if a token is found, a pointer to the beginning of token, otherwise a null pointer.
	//	Calling with NULL instead of c-str causes function to continue scanning where a previous 
	//	successful call to the function ended.
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

void fill_index( int index[])
{
	for (int i=0; i<MAX_LINES_PER_FILE; ++i) {	
		index[i] += 1;
	}
}

char *request_filename(string prompt)
//char request_filename(string prompt)
{
	// Request Filenames From User
	char * filename = (char*) malloc (41);
	char * cstr = new char[prompt.length()+1];
	strcpy(cstr,prompt.c_str());
	cout << cstr << "\n";
	cin >> filename;// Had to use memory allocation in dynamic array to return actual value
	return filename;
}

void bubblesort(string val[], int index[], int MAX_LINES_PER_FILE)
{
	// Bubble largest number toward the right
	//		Note, both val array and an index reference array are sorted using val.
	//		This is meant to allow the reference of index to sort all other arrays filled with input.
	//		An array could probably be used instead of val so that the data stays unchanged..
	for (int i=MAX_LINES_PER_FILE-1; i>0; i--) {
		for (int j = 0; j < i; j++) {
			// pointing to value string as c_str
			char *valstr = new char[val[i].length() + 1];
			char *valstr2 = new char[val[j+1].length() + 1];
			strcpy(valstr, val[j].c_str());
			strcpy(valstr2, val[j+1].c_str());
			
			if(valstr > valstr2) {
				// Swap the numbers
				string tempString = val[j+1];
				int tempIndex = index[j+1];
				val[j+1] = val[j];
				index[j+1] = index[j];
				val[j] = tempString;
				index[j] = tempIndex;
			}
		}
	}
}