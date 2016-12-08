#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string gettag (string& name) 
{
	string temp;
	int i;
	for (i=0; name[i] == '\t'; i++);
	i++;
	for (i; name[i] != '>'; i++)
	{
		temp += name[i];
	}
	name = name.substr(i+1);
	
	cout << temp << endl;
	cout<< name << endl;
	
	return temp;
}

int main()
{
	system("cls");
	int i;
	vector <string> name, street, city, state, zip;
	string line, tag, content;
	ifstream fin("xml.xml");
	getline(fin, line);
	getline(fin, line);
	getline(fin, line);
	
	
	while (line != "</address_book>")
	{
		for (i=1; i<=5; i++)
		{
			getline(fin, line);
			tag = gettag(line);
			int j;
			for (j=0; line[j] != '<'; j++);
			line.erase(j);
			
			
		}
		getline(fin, line);
		
	}
	
}

