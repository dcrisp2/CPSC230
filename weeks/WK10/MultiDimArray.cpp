// Author:		DAN CRISP
// DATE:		3NOV2016
// FILE:		MultiDimArray
/*	DESC	*/

#include<iostream>
#include<cstdlib>
#include<cmath>

int main()
{
	using namespace std;
	int t, i, num[3][4], nums[3][4];
	system("cls");
	
	int count = 1;
	int idim = 4;
	int tdim = 3;
	
	cout << "\nWe're making a multidimensional array.\n";
	for (t=0; t<3; ++t) {
		for (i=0; i<4; ++i) {
			num[t][i] = count;
			cout << num[t][i] << "\t";
			count++;
		}
		cout << "\n";
	}
	
	cout << "\n\n";
	
	for (t=0; t<tdim; ++t) {
		for (i=0; i<idim; ++i) {
			nums[t][i] = (idim-i)+4*tdim;
			cout << num[t][i] << "\t";
		}
		cout << "\n";
	}
	
	
	
	// Could not get this to work
	/*for (int x : num ) {
		cout << x << "\t";
	}*/
	
	return 0;
}