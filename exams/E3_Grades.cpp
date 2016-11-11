//AUTHOR:	Manmeet Singh & Dan Crisp
//DATE:		10Nov2016
//FILE:		Exam3.cpp
/* Report Card*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;
const int NUMBER_OF_STUDENTS = 5, NUMBER_OF_GRADE_VALUES = 4;


int main() {
	// Clear Screen
	system("cls");
	
	// Create arrays for storing student names, grades, totals, and the class average
	string student[NUMBER_OF_STUDENTS] = {"Dan", "Savi", "Ben", "George", "Lisa"};
	int scores [NUMBER_OF_STUDENTS][NUMBER_OF_GRADE_VALUES];
	double sum [NUMBER_OF_STUDENTS], avg[NUMBER_OF_STUDENTS], classAvg(0);
	
	// Seed random value using time
	srand(time(NULL));
	
	// Display Desc and Table Header
	cout << "\nAUTHORS:\tManmeet Singh & Dan Crisp\n"
		<< "DATE:\t\tThursday, November 10th\n"
		<< "DESC:\t\tEXAM 3\n\n";
	cout << "\nNAMES\t#1\t#2\t#3\t#4\tSUM\tAVG\n\n";
	
	for (int i=0;i<NUMBER_OF_STUDENTS;++i) {
		// cout does not print out type string, though it does output c_str (w/ '/0' char ending).
		// creating char pointer strcopied, pointing to new char variable with length +1 of string for needed '/0' c_str ending. 
		char *strcopied = new char[student[i].length() + 1];
		// Copying c_str casted student name to pointer strcopied.
		strcpy(strcopied, student[i].c_str());
		// Using new c_str to console output
		cout << strcopied << "\t";
		
		// Fill 2-dim array with random numbers.
		for (int j=0;j<NUMBER_OF_GRADE_VALUES;++j) {
			scores[i][j] = rand() % (95-70) + 70;
			sum[i] += scores[i][j];
			cout << scores[i][j] << "\t";
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