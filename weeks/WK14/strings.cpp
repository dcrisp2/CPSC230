//AUTHOR:		DANIEL CRISP
//DATE:			Tuesday, November 22nd, 2016
//DESC:			strings.cpp
/*


*/

#include<cstdlib>
#include<cstring>
#include<iostream>

int main()
{
	using namespace std;
	
	char s1[80];
	char s2[80];
	
	strcpy(s1, "c++");
	strcpy(s2, " IS Power Programming.");
	//strcpy(s2, "c++");
	
	cout << "Length of s1: " << strlen(s1) << "\n";
	cout << "Length of s2: " << strlen(s2) << "\n";
	
	cout << "\nComparing strings, strcmp returns: " << strcmp(s1,s2) << "\n";
	
	if(!strcmp(s1,s2)) {
		cout << "Samesies.\n";
	} else {
		cout << "NOT SAME!\n";
	}
	
	
	
	
	
	
	return 0;
}