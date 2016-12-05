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
const int MAX_LINES_PER_FILE = 500;
const int MAX_LINES_IN_MAPFILE = 3600;
const char* ROCS_DELIMITER = " ,#"; //added comma
const char* MAP_DELIMITER = " ,";
const char* NAME_DELIMITER = "_:";

void get_data( istream& , string* , string* , string* , string* , int );
void get_data( istream& , string* , string* , int );
//void get_data( string* , int );
void put_data( ostream& , string* , string* , string* , string* , int );
void put_data( ostream& , string* , string* , int );
void fill_index( int index[]); //Are we sure we actually need to be as specific as to say 'index[]'?
void bubblesort( string val[], int index[], int MAX_LINES_PER_FILE);
char *request_filename(string);
//char request_filename(string);
void translate_data(string* , string* , string* , string* , int num[]);

int main()
{
	system("cls");
	
	string name_set[MAX_LINES_PER_FILE] = {""};
	string value_set[MAX_LINES_PER_FILE] = {""};
	string name_read[MAX_LINES_PER_FILE] = {""};
	string value_read[MAX_LINES_PER_FILE] = {""};
	string name_old[MAX_LINES_IN_MAPFILE] = {""};
	string name_new[MAX_LINES_IN_MAPFILE] = {""};

	char inpfile[40] = {""};
	char outfile[40] = {""};
	char mapfile[40] = {"aliasmap.csv"};
	char reprintData[40] = {"reprintData"};
	char reprintMap[40] = {"reprintMap"};
	int num[] = {0, 0};
	//int done[] = {0, 0, 0};

	//char sortOption;
	int index[MAX_LINES_PER_FILE];
	fill_index(index);
	
	// Request Saveset Filename From User
	strcpy(inpfile,request_filename("Enter saveset filename:\n"));
	
	/*-----GET SAVESET DATA-----*/
	ifstream fin;
	fin.open(inpfile);
	if (!fin.good())
		return 1;
	
	cout << "\nGETTING INPUT...\n";
	int i = 0;
	while (!fin.eof()) {
		get_data(fin, name_set, value_set, name_read, value_read, i);
		i++;
	}
	num[0] = i-1; //for input arrays
	cout << "\tExiting save file. Non-null data of length " << num[0] << "\n";
	fin.close();
	
	
	/*-----PRINT SAVESET DATA-----*/
	ofstream fout;
	fout.open(reprintData);
	if(!fout.good())
		return 1;
	
	cout << "\nPRINTING SAVESET DATA TO 'reprintData'...\n";
	for (int i = 0; i < num[0]; i++) {
		put_data(fout, name_set, value_set, name_read, value_read, i);
	}
	fout.close();
	
	
	/*char *setStr = new char[name_set[0].length() + 1];
	strcpy(setStr, name_set[0].c_str());
	cout << "\nj: " << 0 << "\tGets us " << setStr << "...";
	delete [] setStr;*/
	
	
	/*-----GET ALIASMAP DATA-----*/
	ifstream finMap; //map file
	finMap.open(mapfile);
	if (!finMap.good())
		return 1;
	
	cout << "\nGETTING ALIASMAP...\n";
	i = 0;
	while (!finMap.eof()) {
			get_data(finMap, name_old, name_new, i);
			
			
			i++;
	}
	num[1] = i-1; //re-used for aliasmap data
	cout << "\tExiting aliasmap.csv. Non-null data of length " << num[1] << "\n";
	finMap.close();
	
	
	/*-----PRINT ALIASMAP DATA-----*/
	ofstream foutMap;
	foutMap.open(reprintMap);
	if(!foutMap.good())
		return 1;
	
	cout << "\nPRINTING ALIASMAP TO 'reprintMap'...\n";
	for (int i = 0; i < num[1]; i++) {
		put_data(foutMap, name_old, name_new, i);
	}
	foutMap.close();
	
	
	/*string Str = ("REA_BTS23:PSD_D1155:I_CSET");
	for (int j = 0; j < num[0]; ++j) {
		if (Str.compare(name_set[j])==0) {
			cout << "\nFound set at j equals " << j << endl;
		} else if (Str.compare(name_read[j])==0) {
			cout << "\nFound read at j equals " << j << endl;
		} else if (j==num[0]-1) {
			cout << "\nNOT FOUND\n";
		}
	}*/
	
	/*-----TRANSLATE SAVESET DATA-----*/
	translate_data(name_old, name_new, name_set, name_read, num);
	
	
	/*-----PROBING FUNNY BUSINESS WITH TRANSLATION STARTING IN BTS30-----*/
	fout.open("rereprintData");
	if(!fout.good())
		return 1;
	
	cout << "\nPRINTING SAVESET DATA TO 'reprintData'...\n";
	for (int i = 0; i < num[0]; i++) {
		put_data(fout, name_set, value_set, name_read, value_read, i);
	}
	fout.close();
	
	
	/*-----PARSING NEWNAMES-----*/
	for (int i = 0; i < num[0]; i++) {
		
	}
	
	

	return 0;
}




/*------------------------------------------------------------------------------
FUNCTION GET DATA:

--------------------------------------------------------------------------------*/
void get_data(istream& fin, string* name_set, string* value_set, string* name_read, string* value_read, int i)
{
	//Get saveset data for channel names and their stored values, filling name_set, name_read, and value equivalents string arrays.
	//char character;
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
	splitThing = strtok (thing,ROCS_DELIMITER);
	while (splitThing != NULL) {
		switch(count) {
			case 0:
				name_set[i] = splitThing;
				splitThing = strtok (NULL, ROCS_DELIMITER);
			case 1:
				value_set[i]= splitThing;
				splitThing = strtok (NULL, ROCS_DELIMITER);
			case 2:
				name_read[i] = splitThing;
				splitThing = strtok (NULL, ROCS_DELIMITER);
			case 3:
				value_read[i] = splitThing;
				splitThing = strtok (NULL, ROCS_DELIMITER);
		}
		count++;
	}
	delete [] thing;
}

void get_data(istream& fin, string* name_old, string* name_new, int i)
{
	//Get name mapping data from aliasmap.txt, filling name_old and name_new string arrays.
	//char character;
	char* thing = new char[MAX_CHARS_PER_LINE];
	char * splitThing;
	int count = 0;
	
	while (fin.peek()=='#') {
		fin.getline(thing,MAX_CHARS_PER_LINE);
	}
	
	fin.getline(thing,MAX_CHARS_PER_LINE);
	
	splitThing = strtok (thing,MAP_DELIMITER);
	while (splitThing != NULL) {
		switch(count) {
			case 0:
				name_old[i] = splitThing;
				splitThing = strtok (NULL, MAP_DELIMITER);
			case 1:
				name_new[i]= splitThing;
				splitThing = strtok (NULL, MAP_DELIMITER);
		}
		count++;
	}
	delete [] thing;
}

/*void get_data( string* name, int i)
{
	//filling name class object's properties with parsed values.
	char* thing = new char[MAX_CHARS_PER_LINE];
	char * splitThing;
	int count = 0;
	
	//getline(c-string, numchars )
	//fin.getline(thing,MAX_CHARS_PER_LINE);
	strcpy(thing,name[i]);
	
	splitThing = strtok (thing,NAME_DELIMITER);
	while (splitThing != NULL) {
		switch(count) {
			case 0:
				//--SYSTEM--
				name_set[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 1:
				//--SUBSYSTEM--
				value_set[i]= splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 2:
				//--DEVICE--
				name_read[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 3:
				//--INSTANCE--
				value_read[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 4:
				//--SIGNAL--
				value_read[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 5:
				//--DOMAIN--
				value_read[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 6:
				//--SUFFIX--
				value_read[i] = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
		}
		count++;
	}
	delete [] thing;
}*/


void put_data(ostream& fout, string* name_set, string* value_set, string* name_read, string* value_read, int i)
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
	//		can't cout type string*, had to copy into char first. ...may want to 'normalize' or standardize IO for this function to get more use out of it
	fout << i << " (" << namestr << ",  " << valuestr << ",  " << namestr2 << ",  " << valuestr2 << ")\n";
	//cout << i << " (" << namestr << ",  " << valuestr << ",  " << namestr2 << ",  " << valuestr2 << ")\n";
	delete [] namestr;
	delete [] valuestr;
	delete [] namestr2;
	delete [] valuestr2;
}

void put_data(ostream& fout, string* name_old, string* name_new, int i)
{
	char *oldstr = new char[name_old[i].length() + 1];
	char *newstr = new char[name_new[i].length() + 1];
	
	strcpy(oldstr, name_old[i].c_str());
	strcpy(newstr, name_new[i].c_str());
	
	// Display output to fout and screen
	//		can't cout type string*, had to copy into char first. ...may want to 'normalize' or standardize IO for this function to get more use out of it
	fout << i << " (" << oldstr << ",  " << newstr << ")\n";
	//cout << i << " (" << oldstr << ",  " << newstr << ")\n";
	delete [] oldstr;
	delete [] newstr;
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
	delete [] cstr;
	
	cin >> filename;// Had to use memory allocation in dynamic array to return actual value
	return filename;
}

void translate_data(string* name_old, string* name_new, string* name_set, string* name_read, int num[])
{
	int done[] = {0, 0, 0};
	for (int j = 0; j < num[0]; j++) {
		char *setStr = new char[name_set[j].length() + 1];
		char *readStr = new char[name_read[j].length() + 1];
		strcpy(setStr, name_set[j].c_str());
		strcpy(readStr, name_read[j].c_str());
		cout << "\n(j = " << j << ")\n" << setStr << "\n" << readStr << "\n";
		
		done[0]=0;
		done[1]=0;
		done[2]=0;
		for (int i = 0; i <= num[1]; ++i) {
			char *oldStr = new char[name_old[i].length() + 1];
			char *newStr = new char[name_new[i].length() + 1];
			strcpy(oldStr, name_old[i].c_str());
			strcpy(newStr, name_new[i].c_str());
			
			if (name_set[j].compare(name_old[i])==0&&done[0]==0) {
				//cout << "\nNow " << setStr << " is equal to " << oldStr << " when (i,j) equal " << i << " and " << j << ".\nSo its translation is:\t";
				name_set[j].replace(0,name_old[i].length(),name_new[i]);
				//cout << "\t..found " << newStr << "\n";
				done[0]=1;
				done[2]=done[0]+done[1];
			} else if (name_read[j].compare(name_old[i])==0 && done[1]==0) {
				//cout << "\nNow " << readStr << " is equal to " << oldStr << " when (i,j) equal " << i << " and " << j << ".\nSo its translation is:\t";
				name_read[j].replace(0,name_old[i].length(),name_new[i]);
				//cout << "\t..found " << newStr << "\n";
				done[1]=1;
				done[2]=done[0]+done[1];
			} else if (done[2]==2) {
				i = num[1];
				cout << "\nBOTH FOUND\n";
			}
			
			if (done[2]==0 && i==num[1]) {
				cout << "\nMISSING BOTH(j = " << j << "):";
				cout << "\n" << setStr
					<< "\n" << readStr << "\n";
			} else if (done[0]==0 && done[2]==1 && i==num[1]) {
				cout << "\nMISSING SET(j = " << j << "):\n" << setStr << "\n";
			} else if (done[1]==0 && done[2]==1 && i==num[1]) {
				cout << "\nMISSING READ(j = " << j << "):\n" << readStr << "\n";
			} else {
				//cout << "\nError?\n";
			}
			delete [] oldStr;
			delete [] newStr;
		}
		delete [] setStr;
	}
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
