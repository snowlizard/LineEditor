// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>

using namespace std;

void menu();

bool checkExtension(string);
fstream createFile(string);
void getFile(fstream&);

vector<string> storeFile(fstream&);
void displayFile(vector<string>);

int main()
{
	fstream file;
	string line;
	vector<string>fileVector;

	while (!file.is_open()) {
		getFile(file);
	}
	
	fileVector = storeFile(file);
	//displayFile(fileVector);

	menu();

	return 0;
}



bool checkExtension(string filename)
{
	// checks filename extension ends in .txt

	int strlen = filename.length();
	int temp = 0, extLen = 4;
	string extension;

	temp = filename.length() - (extLen);

	if (strlen >= extLen) {
		for (int i = 0; i < (extLen); i++)
		{
			extension += filename[temp + i];
		}

		if (extension == ".txt" && strlen == extLen) {
			return false;
		}
		else if (extension == ".txt")
			return true;
		else
			return false;
	}
	else
		return false;
}

fstream createFile(string filename)
{
	fstream file;

	file.open(filename);

	if (!file.is_open()) {
		file.open(filename, fstream::out);
	}

	return file;
}

void getFile(fstream& file)
{
	char userInput; 
	string filename;

	std::cout << "would you like to open a file or create a new file? [ O / C ]\n";
	cin >> userInput;

	while (toupper(userInput) != 'O' && toupper(userInput) != 'C')
	{ 
		std::cout << "Please enter 'O' to open file or 'C' : to create new file.\n";
		cin >> userInput;
	}

	if (toupper(userInput) == 'C') {
		std::cout << "Enter name of file you want to create.\n";
		std::cin >> filename;

		while (!checkExtension(filename))
		{
			std::cout << "filename must in with file extension .txt\n";
			std::cin >> filename;
		}
		file = createFile(filename);
	}

	else if (toupper(userInput) == 'O')
	{
		std::cout << "Enter name of file you want to open.\n";
		std::cin >> filename;

		while (!checkExtension(filename))
		{
			std::cout << "filename must end with file extension .txt\n";
			std::cin >> filename;
		}

		//fstream file;
		file.open(filename);

		if (!file.is_open()) {
			std::cout << "file does not exist.\n";
		}
	}
}

vector<string> storeFile(fstream &filename)
{
	// return vector<string> of file contents.

	string line;
	vector<string> readFile;
	vector<int> fileLines;
	int i = 0;

	while (!filename.eof()) {

		fileLines.push_back(i);
		i++;

		getline(filename, line);
		readFile.push_back(line);
	}


	return readFile;
}


void displayFile(vector<string> file)
{
	// displays current contents of file

	int fileSize = file.size();
	int counter = 0;

	while (counter < fileSize)
	{
		std::cout << file[counter] << endl;
		counter++;
	}
}

void menu()
{	// initialize menu variables 
	int userInput;

	const int MENU_SIZE = 13;

	string menuWords[MENU_SIZE] = { "1. substitute",
		"2. copy",
		"3. locate",
		"4. delete",
		"5. move",
		"6. print",
		"7. insert",
		"8. type",
		"9. paste",
		"10. replace",
		"11. open file",
		"12. new file",
		"13. quit" };

	// ask user what he/she would like to do
	std::cout << "What would you like to do? [ enter number ]\n";

	// display menu 
	for (int i = 0; i < MENU_SIZE; i++)
	{
		std::cout << menuWords[i] << endl;
	}
	// get user input
	std::cout << ": ";
	std::cin >> userInput;

	// input invalidation
	if (userInput < 0 || userInput > MENU_SIZE) {
		do {
			std::cout << "Incorrect value entered. Try again.\n";
			std::cin >> userInput;
		} while (userInput < 0 || userInput > MENU_SIZE);
	}

	switch (userInput)
	{
	case 1:
		// sub
		break;
	case 2:
		// copy
		break;
	case 3:
		//locate
		break;
	case 4:
		// delete
		break;
	case 5:
		// move
		break;
	case 6:
		//print
		break;
	case 7:
		// insert
		break;
	case 8:
		//type
		break;
	case 9:
		// paste
		break;
	case 10:
		// replace
		break;
	case 11:
		// open file
		break;
	case 12:
		// new file
		break;
	case 13:
		// quit
		break;
	}


}