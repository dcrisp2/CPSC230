//AUTHOR:		DANIEL CRISP
//DATE:			Tuesday, November 22nd, 2016
//DESC:			classApp.cpp
/*


*/

#include<iostream>

using namespace std;
//my classes
class vehicle
{
		int mpg, capacity;
	public:
		void set_values (int, int);
		int num_passengers;
		int range() {return mpg*capacity;}
};

void vehicle::set_values (int x, int y) {
	mpg = x;
	capacity = y;
}


int main()
{
	int range1, range2;
	
	vehicle minivan;
	vehicle sportcar;
	
	minivan.num_passengers = 8;
	minivan.set_values(28,15); //mpg and capacity
	
	sportcar.num_passengers = 2;
	sportcar.set_values(25,11);
	
	range1 = minivan.range();
	range2 = sportcar.range();
	
	cout << "\nA Minivan carries " << minivan.num_passengers 
		<< " and it can travel " << range1 
		<< " miles on a full tank.\n";

	cout << "\nA Sportcar carries " << sportcar.num_passengers 
		<< " and it can travel " << range2 
		<< " miles on a full tank.\n";

	cout << "\nThis is a difference in range of " << range2-range1 << " miles.\n\n";
	
	return 0;
}