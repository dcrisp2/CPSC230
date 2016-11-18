//AUTHOR:	Dan Crisp
//DATE:		Thursday, November 17th
//FILE:		makegrade.cpp
/* Report Card*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;
const int NUMBER_OF_STUDENTS = 5, NUMBER_OF_QUESTIONS = 10;

int main()
{
	// Clear Screen
	system("cls");
	
	// Create arrays for storing student names, grades, totals, and the class average
	char student_answers [NUMBER_OF_STUDENTS][NUMBER_OF_QUESTIONS];
	char correct_answers [NUMBER_OF_QUESTIONS];
	double sum [NUMBER_OF_STUDENTS] = {0,0,0,0,0};
	
	
	ifstream fin;
	fin.open("studentAnswers.txt");
	
	ifstream fin_key;
	fin_key.open("answer_key.txt");
	
	
	//cout << "\nANSWERKEY:\n";

	
	for (int i=0; i<NUMBER_OF_STUDENTS; ++i) {
		for (int j = 0; j<NUMBER_OF_QUESTIONS; ++j){
			fin >> student_answers [i][j];
			//cout << student_answers [i][j] << "\t";
		}
	}
	//cout << "\n";
	
	

	//cout << "\nSTUDENT ANSWERS:\n";
	for (int j = 0; j<NUMBER_OF_QUESTIONS; ++j) {
		fin_key >> correct_answers [j];
		//cout << correct_answers [j] << "\t";
		
		for (int i = 0; i<NUMBER_OF_STUDENTS; ++i) {
			if (correct_answers [j]==student_answers [i][j]) {
				sum[i] += 10;
			}
		}

	}

	cout << "STUDENT\t# CORRECT\tSCORE\n";
	for (int i=0; i<NUMBER_OF_STUDENTS; ++i) {
		cout << i+1 << "\t" << sum[i]/10 << "\t\t" << sum[i] << "\n";
	}
	
	
	fin.close();
	fin_key.close();
	return 0;
}