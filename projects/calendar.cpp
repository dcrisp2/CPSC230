#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

string months[13] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int daysPerMonth(int, int);

int main()
{
	system("cls");
	
	int i = 0;
	
	cout<< "Enter month and year.\n";
	cin>> month >> year;
	//1-1-1901 was Tuesday
	
	int FourYears, OneYears, daysPassed;
	FourYears = (year-1901)/4;
	OneYears = (year-1901)%4;
	
	daysPassed = (FourYears*1461) + OneYears*365;
	for (i=1; i < month; i++)
		daysPassed += daysPerMonth(i, year);
	
	cout << "there have been " << daysPassed <<
		"days between 1-1-1901 and " << month <<
		"-1-" << year << endl;
	
	//Calendar Output
	
	spaces = (2 + daysPassed)%7;
	cout << months[month] << " " << year << "\n"
	
	" S  M  T  W  T  F  S " << endl;
	
	for (i=1; i<=spaces; i++)
		cout << "   ";
	for (i=1; i <=daysPerMonth(month, year); i++)
	{
		cout << setw(3) << i;
		if ((i+spaces)%7 == 0) //End of week
			cout << endl;
	}
	cout << "\n\n";
	
	return 0;
}



int daysPerMonth(int month, int year)
{
	int days[13] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if (month != 2)
		return days[month];
	else if (month==2 && year%4 ==0)
		
	
}