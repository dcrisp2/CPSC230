//AUTHOR:	Manmeet Singh & Dan Crisp
//DATE:		Tuesday, November 15th
//FILE:		Exam3.cpp
/* Report Card*/
#include<fstream>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>

using namespace std;
const int NUMBER_OF_STUDENTS = 5, NUMBER_OF_GRADE_VALUES = 4;
const int FILE_IO_MODE = 1;

char *request_filename(string);
void makefiles();
void display_header();


int main() {
	// Clear Screen
	system("cls");
	
	// Create arrays for storing student names, grades, totals, and the class average
	string student[NUMBER_OF_STUDENTS] = {"Dan", "Savi", "Ben", "George", "Lisa"};
	int scores [NUMBER_OF_STUDENTS][NUMBER_OF_GRADE_VALUES], haveFile(0);
	double sum [NUMBER_OF_STUDENTS], avg[NUMBER_OF_STUDENTS], classAvg(0);
	
	// Request Filenames From User
	char *inpfile = request_filename("Enter input filename:\n");
	char *outfile = request_filename("Enter output filename:\n");
	
	
	for (int i=0;i<NUMBER_OF_STUDENTS;++i) {
		// cout does not print out type string, though it does output c_str (w/ '/0' char ending).
		// creating char pointer strcopied, pointing to new char variable with length +1 of string for needed '/0' c_str ending. 
		char *strcopied = new char[student[i].length() + 1];
		// Copying c_str casted student name to pointer strcopied.
		strcpy(strcopied, student[i].c_str());
		// Using new c_str to console output
		cout << strcopied << "\t";
		
		if (!FILE_IO_MODE) {
			//Seed random value using time
			srand(time(NULL));
			
			// Fill 2-dim array with random numbers.
			for (int j=0;j<NUMBER_OF_GRADE_VALUES;++j) {
				scores[i][j] = rand() % (95-70) + 70;
				sum[i] += scores[i][j];
				cout << scores[i][j] << "\t";
			}
		}
		
		avg[i] = sum[i]/NUMBER_OF_GRADE_VALUES;
		cout << sum[i] << "\t" << avg[i] << "%\n";
		
		// Having classAvg do double duty, holding aggregated sum for each student.
		classAvg += sum[i];
	}
	
	cout << "\n\nCLASS SUM:\t" << classAvg << "\n";
	cout << "\n# GRADES:\t" << ((NUMBER_OF_STUDENTS)*(NUMBER_OF_GRADE_VALUES)) << "\n";
	
	classAvg = classAvg/((NUMBER_OF_STUDENTS)*(NUMBER_OF_GRADE_VALUES));
	
	cout << "\nCLASS AVERAGE:\t" << classAvg << "%\n\n";
	
	return 0;
}

char *request_filename(string prompt)
{
	// Request Filenames From User
	char * filename = (char*) malloc (41);
	char * cstr = new char[prompt.length()+1];
	strcpy(cstr,prompt.c_str());
	cout << cstr << "\n";
	cin >> filename;// Had to use memory allocation in dynamic array to return actual value
	return filename;
}

void makefiles()
{
	char *outfile = request_filename("Enter output filename:\n");
	
	ofstream fout;
	fout.open(outfile);
	if (!fout.good())
		cout << "outfile in makefiles is no good.\n";
		//return 1; //void cannot return value
	
	for (int j=0;j<NUMBER_OF_GRADE_VALUES;++j) {
		fout << rand() % (95-70) + 70 << "\n";
	}
	
	fout.close();
}

void display_header() {
	// Display Desc and Table Header in console
	cout << "\nAUTHORS:\tManmeet Singh & Dan Crisp\n"
		<< "DATE:\t\tThursday, November 10th\n"
		<< "DESC:\t\tEXAM 3\n\n";
	cout << "\nNAMES\t#1\t#2\t#3\t#4\tSUM\tAVG\n\n";
