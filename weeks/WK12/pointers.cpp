#include<iostream>

int main()
{
	system("cls")
	using namespace std;
	int size, i;
	int *p, *pointer;
	cout << "Enter the size for the array: ";
	cin>> size;
	p=new int[size];
	for (i=0; i<size; ++i)
		p[i]=i;
	for (i=0; i<size; ++i)
		cout << p[i] << endl;
	system("pause");
	
	int *pointer, *pointer
	cout << &size;
	system("pause");
	p=&i;
	cout << *p << endl;
	*p = 7;
	cout << i << endl;
	cout << &p;
	
	/*
	For an already assigned pointer p *p is the value of the variable p points at.
	
	p is the memory location of the variable that p points at.
	
	&p is the address of the pointer p itself.
	*/
	
	return 0;
}