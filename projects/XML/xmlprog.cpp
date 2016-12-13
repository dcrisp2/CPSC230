#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

class contact
{
public:
	contact(string name, string street, string city, string state, string zip)
	{
		contact::name = name;
		contact::street = street;
		contact::city = city;
		contact::state = state;
		contact::zip = zip;
	}

	string name;
	string street;
	string city;
	string state;
	string zip;
};

string gettag(string name)
{
	string tag = "";
	int startIndex = name.find_first_of('<');
	int endIndex = name.find_first_of('>', startIndex+1);
	
	if (startIndex != string::npos && endIndex != string::npos)
	{	
		tag = name.substr(startIndex + 1, endIndex - startIndex - 1);
	}
	
	return tag;
}

string getdata(ifstream &fin, string line) {
	getline(fin, line);	
	string tag = gettag(line);

	string tab = "\t";
	string opentag = "<" + tag + ">";
	string endtag = "</" + tag + ">";

	while (true) {
		int tabIndex = line.find(tab);
		if (tabIndex == string::npos)
			break;
		line.erase(tabIndex, tab.length());
	}
	
	//Position where opentag starts
	int start = line.find(opentag);
	//Erase opentag from 'line'
	line.erase(start, opentag.length());

	//Position where endtag starts
	int end = line.find(endtag);
	//Erase endtag from 'line'
	line.erase(end, endtag.length());
	
	return line;
}

vector<contact> filter_contacts(vector<contact> contacts, string city)
{
	vector<contact> filtered;

	for (int i = 0; i < contacts.size(); i++)
	{
		contact person = contacts[i];
		if (person.city == city)
		{
			filtered.push_back(person);
		}
	}

	return filtered;
}

vector<contact> filter_contacts(vector<contact> contacts, int start_zip, int end_zip)
{
	vector<contact> filtered;
	
	for (int i = 0; i < contacts.size(); i++)
	{
		contact person = contacts[i];
		if (atoi(person.zip.data()) >= start_zip && atoi(person.zip.data()) <= end_zip)
		{
			filtered.push_back(person);
		}
	}

	return filtered;
}

void display_contacts(vector<contact> contacts)
{
	for (int i = 0; i < contacts.size(); i++)
	{
		contact person = contacts[i];
		cout << "-----------------" << endl;
		cout << "Name: " << person.name << endl;
		cout << "-----------------" << endl;
		cout << "Street: " << person.street << endl;
		cout << "City: " << person.city << endl;
		cout << "State: " << person.state << endl;
		cout << "Zip: " << person.zip << endl;
		cout << "\n";
	}
}

int main()
{
	system("cls");
	int i;
	int preChecked = 0;

	vector<contact> contacts;
	vector<contact> filtered_city;
	vector<contact> filtered_zip;

	string line, tag, content;
	ifstream fin("xml.xml");

	//Discard <?xml version="1.0"?>
	getline(fin, line);
	//Discard <address_book>
	getline(fin, line);

	while (line != "</address_book>")
	{
		//Discard <contact>
		if (preChecked == 0) {
			getline(fin, line);
		}


		string name = getdata(fin, line);
		string street = getdata(fin, line);
		string city = getdata(fin, line);
		string state = getdata(fin, line);
		string zip = getdata(fin, line);
		
		contact person(name, street, city, state, zip);
		contacts.push_back(person);

		//Discard </contact>
		getline(fin, line);
		//Discard either <contact> OR </address_book>
		getline(fin, line); //might be good to do a istream::peak for tab char.. though not sure if all xml uses "\t" chars. for now, put to end to catch addressbook.
		//Make sure three lines aren't discarded
		preChecked = 1;

	}
	
	cout << "\nFILTERED BY CITY 'Palmdale': " << endl;
	filtered_city = filter_contacts(contacts, "Palmdale");
	display_contacts(filtered_city);

	cout << "\nFILTERED BY ZIP '90210' to '90214': " << endl;
	filtered_zip = filter_contacts(contacts, 90210, 90214);
	display_contacts(filtered_zip);
}
