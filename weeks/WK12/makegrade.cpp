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
	string student[NUMBER_OF_STUDENTS] = {"Dan", "Savi", "Ben", "George", "Lisa"};
	char student_answers [NUMBER_OF_STUDENTS][NUMBER_OF_QUESTIONS];
	double sum [NUMBER_OF_STUDENTS];
	char correct_answers[NUMBER_OF_QUESTIONS], next;
	
	char inpfile[40] = {""};
	char outfile[40] = {""};
	char answerKey[40] = {"answer_key.txt"};
	

	cout << "Enter filename for input:\n";
	cin >> inpfile;
	cout << "Enter filename for output:\n";
	cin >> outfile;
	
	
	ifstream fin;
	fin.open(inpfile);
	if (!fin.good())
		return 1;
	
	ofstream fout;
	fout.open(outfile);
	if (!fout.good())
		return 1;
	
	ifstream fin_key;
	fin_key.open(answerKey);
	if (!fin_key.good())
		return 1;
	
	
	cout << "\nGETTING ANSWERKEY:\n";
	fout << "\nANSWER KEY:\n";
	int i = 0; int j = 0;
	while (!fin_key.eof()) {
		fin_key >> next;
		fout << next << "\t";
		cout << next << "\t";
		
		if (i == NUMBER_OF_QUESTIONS) {
			i = 0;
			j = 1;
			cout << "\n";
		}
		
		correct_answers[i-NUMBER_OF_QUESTIONS]=next;
		
		i++;
	}
	cout << "\n";
	fin_key.close();
	
	
	
	
	
	
	cout << "\nGETTING STUDENT ANSWERS:\n";
	fout << "\nSTUDENT ANSWERS:\n";
	
	int j = 0; i = 0;
	while (!fin.eof()) {
		fin >> next;
		fout << next << "\t";
		cout << next << "\t";
		
		if ( j == NUMBER_OF_QUESTIONS) {
			cout << sum[i] << "\n";
			j = 0;
			i++;
		}
		
		student_answers[i][j-NUMBER_OF_QUESTIONS]=next;
		if (student_answers[i][j-NUMBER_OF_QUESTIONS]==correct_answers[j-NUMBER_OF_QUESTIONS]) {
			sum[i] = sum[i] + 10;
		}
		j++;
	}
	cout << "\n";
	fin.close();
	
	
	
	fout.close();
	
	
	
	
	
	
	
	return 0;
}