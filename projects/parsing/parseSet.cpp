//AUTHOR:	Dan Crisp
//DATE:		27OCT2016
//FILE:		parseSet.cpp
/* Readin and writing data from a text file. */
/* Readin mapping of old-new names, replace any stored names from first file with new ones*/
/* Parse names to make way for new functionality
 - output current beam settings.
 - give user interface to change, then accept new beam settings

}*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<map>

using namespace std;

const int MAX_CHARS_PER_LINE = 100;
const int MAX_LINES_PER_FILE = 500;
const int MAX_LINES_IN_MAPFILE = 3600;
const char* ROCS_DELIMITER = " ,#";
const char* MAP_DELIMITER = " ,";
const char* NAME_DELIMITER = " _:";


class device
{
	private:
		char *setStr, *setVal, *readStr, *readVal;
		char *SYS, *SUB, *DEV, *INST, *SIG, *DOM, *SUFX;
		char *DNUM;
		double Val, newVal;
	
	public:
		device(string s, string sv, string rd, string rdv) {
			set(s, sv, rd, rdv);
		}
		device() {}
		void set(string s, string sv, string rd, string rdv) {
			setStr = strtochar(s);
			setVal = strtochar(sv);
			readStr = strtochar(rd);
			readVal = strtochar(rdv);
		}
		char *strtochar(string str) {
			char *ans = new char[str.length() + 1];
			strcpy(ans, str.c_str());
			return ans;
		}
		void parseMacros();
		void outputMacros() {
			cout << "\n\t{\""
				<< get_sys() << "\",\t\"" 
				<< get_sub() << "\",\t\"" 
				<< get_dev() << "\",\t\"" 
				<< get_inst() << "\",\t\"" 
				<< get_sig() << "\",\t\"" 
				<< get_dom() << "\",\t\"" 
			<< get_sufx() << "\"}\n";
		}
		//memory access issues...
		//Tried this... it sometimes works
		//also tried strncpy(src, length, n) (or something like that)
		//have not yet tried copy(), or successfully attempted stepping pointer through string/char copying memory values to DNUM
		/*void set_dnum() {
			char* thing = new char[5];
			char * splitThing;
			strcpy(thing, INST);
			splitThing = strtok (thing,"DN");
			if (splitThing == NULL) {
				splitThing = strtok (NULL, "DN");
				DNUM = splitThing;
				splitThing = strtok (NULL, "DN");
				cout << "\ninside set_dnum, where splitThing == NULL.";
			} else if (splitThing != NULL ) {
				DNUM = splitThing;
				cout << "\ninside set_dnum, where splitThing != NULL.";
			}
			if (!DNUM) {
				DNUM = "";
			}
			delete [] thing;
		}*/
		
		char *get_sys() {return SYS;}
		char *get_sub() {return SUB;}
		char *get_dev() {return DEV;}
		char *get_inst() {return INST;}
		char *get_sig() {return SIG;}
		char *get_dom() {return DOM;}
		char *get_sufx() {
			if (!SUFX) {
				SUFX = "";//says it's deprecated in g++
			}
			return SUFX;
			}
		char *get_dnum() {return DNUM;}
		
		char *get_setStr() {return setStr;}
		char *get_setVal() {return setVal;}
		char *get_readStr() {return readStr;}
		char *get_readVal() {return readVal;}
		
		//double get_newVal() {return newVal;}
};

void get_data( istream& , string* , string* , string* , string* , int );
void get_data( istream& , string* , string* , int );
void put_data( ostream& , string* , string* , string* , string* , int );
void put_data( ostream& , string* , string* , int );
void bubblesort( string val[], int index[], int MAX_LINES_PER_FILE);
char *request_filename(string);
void translate_data(string* , string* , string* , string* , int num[]);
string translate_data(map<string, string>& aliasmap, string str);


/*################################################################################
	DRIVER FUNCTION:
	
################################################################################*/
int main()
{
	system("cls");
	
	string name_set[MAX_LINES_PER_FILE] = {""};
	string value_set[MAX_LINES_PER_FILE] = {""};
	string name_read[MAX_LINES_PER_FILE] = {""};
	string value_read[MAX_LINES_PER_FILE] = {""};
	string name_old[MAX_LINES_IN_MAPFILE] = {""};
	string name_new[MAX_LINES_IN_MAPFILE] = {""};
	
	map <string, string> aliasmap; //made in get_data loop for alias map, used to translate during get_data loop for saveset data
	vector <device> data;
	data.reserve(MAX_LINES_PER_FILE);
	
	char inpfile[40] = {""};
	char mapfile[40] = {"aliasmap.csv"};
	char reprintData[40] = {"reprintData"};
	char reprintMap[40] = {"reprintMap"};
	int num[] = {0, 0}; //num[0] for saveset data, num[1] for aliasmap
	int i = 0;
	

	/*-----------------------
		GET ALIASMAP DATA
	-----------------------*/
	ifstream finMap;
	finMap.open(mapfile);
	if (!finMap.good())
		return 1;
	
	cout << "\nGETTING ALIASMAP...\n";
	while (!finMap.eof()) {
			get_data(finMap, name_old, name_new, i);
			aliasmap[name_old[i]] = name_new[i]; //So a query using old name, retrieves a new one!
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
	
	
	/*-------------------------------------
		GET SAVESET DATA & TRANSLATE IT
	-------------------------------------*/
	strcpy(inpfile,request_filename("\nEnter saveset filename:"));
	
	ifstream fin;
	fin.open(inpfile);
	if (!fin.good())
		return 1;
	
	cout << "\nGETTING INPUT...\n";
	i = 0;
	while (!fin.eof()) {
		get_data(fin, name_set, value_set, name_read, value_read, i);
		name_set[i] = translate_data( aliasmap, name_set[i]);
		name_read[i] = translate_data( aliasmap, name_read[i]);
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
	
	
	/*-----PARSING NEWNAMES-----*/
	//loop through saveset data
	for (int k = 0; k < num[0]; k++) {
		device d(name_set[k], value_set[k], name_read[k], value_read[k]);
		d.parseMacros();
		//d.outputMacros();
		data.push_back(d);
	}
	cout << "HEY!" << endl;
	/*data[0].set_dnum();
	cout << "\nFor data[0].set_dnum, DNUM = " << data[0].get_dnum() << "\n";*/
	
	
	fout.open("usersub");
	if (!fout.good())
		return 1;
	cout << "\n\nMaking db file from objects:\n";
	for (int k = 0; k<)

	return 0;
}


/*################################################################################
	FUNCTION DEFINITIONS:
	
==================================================================================
	GETTING DATA:
==================================================================================*/
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


/*================================================================================
	OUTPUTTING DATA:
================================================================================*/
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


/*================================================================================
	FILE IO:
================================================================================*/
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


/*================================================================================
	DATA PROCESSING:
================================================================================*/
void device::parseMacros()
{
	//filling name class object's properties with parsed values.
	char* thing = new char[MAX_CHARS_PER_LINE];
	char * splitThing;
	int count = 0;
	
	//getline(c-string, numchars )
	//fin.getline(thing,MAX_CHARS_PER_LINE);
	//thing.copy(setStr);
	strcpy(thing, setStr);
	
	splitThing = strtok (thing,NAME_DELIMITER);
	while (splitThing != NULL) {
		switch(count) {
			case 0:
				//--SYSTEM--
				SYS = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 1:
				//--SUBSYSTEM--
				SUB = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 2:
				//--DEVICE--
				DEV = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 3:
				//--INSTANCE--
				INST = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 4:
				//--SIGNAL--
				SIG = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 5:
				//--DOMAIN--
				DOM = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
			case 6:
				//--SUFFIX--
				SUFX = splitThing;
				splitThing = strtok (NULL, NAME_DELIMITER);
		}
		count++;
	}
	delete [] thing;
}

void translate_data(string* name_old, string* name_new, string* name_set, string* name_read, int num[])
{
	int done[] = {0, 0, 0};
	for (int j = 0; j < num[0]; j++) {
		char *setStr = new char[name_set[j].length() + 1];
		char *readStr = new char[name_read[j].length() + 1];
		strcpy(setStr, name_set[j].c_str());
		strcpy(readStr, name_read[j].c_str());
		//cout << "\n(j = " << j << ")\n" << setStr << "\n" << readStr << "\n";
		
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
				cout << "\nBOTH FOUND (j = " << j << ")\n";
			}
			
			if (done[2]==0 && i==num[1]) {
				cout << "\nMISSING BOTH (j = " << j << "):";
				cout << "\n" << setStr
					<< "\n" << readStr << "\n";
			} else if (done[0]==0 && done[2]==1 && i==num[1]) {
				cout << "\nMISSING SET (j = " << j << "):\n" << setStr << "\n";
			} else if (done[1]==0 && done[2]==1 && i==num[1]) {
				cout << "\nMISSING READ (j = " << j << "):\n" << readStr << "\n";
			} else {
				//cout << "\nError?\n";
			}
			delete [] oldStr;
			delete [] newStr;
		}
		delete [] setStr;
	}
}

string translate_data(map<string, string>& aliasmap, string str)
{
	//Passed a map of old->new names, and the search string. Either a new string, or the same one will be returned
	if (aliasmap.find(str) != aliasmap.end()) {
			str = aliasmap[str];
	}
	return str;
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
