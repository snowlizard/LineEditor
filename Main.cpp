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

#include "commands.h";

using namespace std;

void menu();

bool checkExtension(string);
fstream createFile(string);
void getFile(fstream&);

vector<string> storeFile(fstream&);
void displayFile(vector<string>);

int main()
{
	/* Currently testing parts of program using Main() all statements here do not reflect 
		final program */
	
	fstream file;
	string line;
	vector<string>fileVector;

	while (!file.is_open()) {
		getFile(file);
	}

	Commands cmd;
	cmd.currentIndex = 0;

	fileVector = storeFile(file);
	cmd.list = fileVector;
	
	//cmd.move(fileVector, 2);
	//cmd.move(fileVector, 4);


	//std::cout << "new index =" << cmd.currentIndex << endl;

	//cmd.replace(fileVector, 5);

	displayFile(cmd.list);

	cmd.del(4);

	displayFile(cmd.list);
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
		std::cout << counter << ". " <<  file[counter] << endl;
		counter++;
	}
}

void menu()
{	// initialize menu variables 




}



