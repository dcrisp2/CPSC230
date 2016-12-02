//AUTHOR:		DANIEL CRISP
//DATE:			Tuesday, November 22nd, 2016
//DESC:			vehicleClass.cpp
/*


*/

#include<iostream>

using namespace std;
//my classes
class vehicle
{
	public:
		vehicle(int p, int f, int m) {
			set(p,f,m);
		}
		vehicle() {}
		void input();
		void output();
		void set(int p, int f, int m) {
			num_passengers = p;
			fuel_capacity = f;
			miles_per_gallon = m;
		}
		double get_range() {return miles_per_gallon*fuel_capacity;}
		int get_pass();
		int get_cap();
		int get_mpg();
	private:
		int miles_per_gallon, fuel_capacity, num_passengers; //num_passenger here isn't used.
		double range;
};



void vehicle::input()
{
	cout << "Enter the # of passengers: ";
	cin >> num_passengers;
	cout << "\n";
	cout << "Enter the fuel capacity: ";
	cin >> fuel_capacity;
	cout << "\n";
	cout << "Enter the miles_per_gallon: ";
	cin >> miles_per_gallon;
	cout << "\n";
}

void vehicle::output()
{
	cout << "The number of passengers is " << num_passengers << "\n";
	cout << "The fuel capacity is " << fuel_capacity << "\n";
	cout << "The miles per gallon is " << miles_per_gallon << "\n";
	cout << "\n";
}

int vehicle::get_pass() {
	return num_passengers;
}

int vehicle::get_cap() {
	return fuel_capacity;
}

int vehicle::get_mpg() {
	return miles_per_gallon;
}

int main()
{
	system("cls");
	
	vehicle minivan, sportscar;
	
	cout << "ENTERING VALUES FOR MINIVAN...\n";
	minivan.input();
	cout << "\nMINIVAN\n";
	minivan.output();
	
	
	sportscar.set(2, 12, 20);
	cout << "\nSPORTSCAR\n";
	sportscar.output();
	
	int vehicle_passengers = minivan.get_pass();
	int vehicle_capacity = minivan.get_cap();
	int vehicle_mpg = minivan.get_mpg();
	
	cout << "\nMINIVAN (after using get_nnn() functions)\n";
	minivan.output();
	
	vehicle largevan(12,20,15);
	cout << "\nLARGEVAN\n";
	largevan.output();
	cout << "\nAnd the range of that crazy large family van is " << largevan.get_range() << " miles.\n";
	
	return 0;
}