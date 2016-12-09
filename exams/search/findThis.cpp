#include <iostream>
using namespace std;

int main()
{
	system("cls");
	
	int data[][2] = {{1,2},
					 {2,3},
					 {3,4}};
	
	int find_this;
	
	cout << "find this: ";
	cin >> find_this;
	
	for(int i=0; i<3; i++)
	{
		if(data[i][0] ==find_this)
			cout << "found it" << endl;
		else
			cout << "nope" << endl;
		
	}
	
	
	return 0;
}