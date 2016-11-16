//AUTHOR:	Dan Crisp
//DATE:		3NOV2016
//FILE:		fileArraySort.cpp
/* Readin and writing data from a text file. */
/* Works well for AllAlarmChannels.txt as input, but doens't handle saveset.txt header very well */
#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<cmath>

using namespace std;

// Including this as reference to sorting tool whether I use it or not.
void bubblesort(int arr[], int MAX_LINES_PER_FILE);
const int MAX_LINES_PER_FILE = 10;
const int MAX_CHARS_PER_LINE = 100;

int main ()
{
	system("cls");
	int arr[MAX_LINES_PER_FILE];
	char next[MAX_CHARS_PER_LINE];
	
	char inpfile[40] = {""};
	char outfile[40] = {""};
	

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
	
	
	cout << "\nGETTING INPUT:\n";
	int i = 0;
	while (fin >> next) {
		arr[i] = atoi(next);
		//cout << next << "\t";
		cout << arr[i] << "\t";
		// cout << arr1[i] << "\n";
		i++;
	}
	fin.close();
	
	
	cout << "\n\nSORTING INPUT:\n\n";
	bubblesort(arr, MAX_LINES_PER_FILE);
	
	cout << "DISPLAY SORTED ARRAY:\n";
	for (int i = 0; i<MAX_LINES_PER_FILE; i++) {
		cout << arr[i] << "\t";
		fout << arr[i] << "\n";
	}
	cout << "\n";
	
	fout.close();
	
	return 0;
}

void bubblesort(int arr[], int MAX_LINES_PER_FILE)
{
	
	// Bubble largest number toward the right
	for (int i= MAX_LINES_PER_FILE-1; i>0; i--) {
		for (int j = 0; j < i; j++) {
			if(arr[j] > arr[j+1])
			{
				// Swap the numbers
				int temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}