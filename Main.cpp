#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstring>

#include "commands.h"


using namespace std;

bool checkExtension(string);
fstream createFile(string);

string getFile(fstream&);
vector<string> storeFile(fstream&);

int main()
{
	/* Currently testing parts of program using Main() all statements here do not reflect 
		final program */
	
	fstream file;
	string line;
	vector<string>fileVector;

	string filename = getFile(file);

	fileVector = storeFile(file);
	
	Commands cmd(fileVector, 0, filename);
	
	string mycmd;
	string userInput, userWord;
	int userInt;

	bool running = true;

	cin.ignore();

	while (running)
	{
		std::cout << ">";
		getline(cin, mycmd);

		cmd.parseCmd(mycmd, userInput, userWord, userInt);
		cmd.runCmd(userInput, userWord, userInt);
	}
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


string getFile(fstream& file)
{
	/* gets file name from user and opens or creates file */

	// have to ask user to create or open file

	string filename;
	char input;

	std::cout << " Would you like to open a file or create a new one? [ O / C ] \n";
	std::cin.get(input);
	std::cin.ignore();

	while (toupper(input) != 'O' && toupper(input) != 'C')
	{
		std::cout << "Please enter either [ O or C ] \n";
		std::cin.get(input);
		std::cin.ignore();
	}

	if ( toupper(input) == 'O' )
	{
		std::cout << "Enter the name of the file you wish to open.\n";
		std::cin >> filename;

		while (!checkExtension(filename))
		{
			std::cout << "filename must end in file extension .txt\n";
			std::cin >> filename;
		}

		file.open(filename, ios::in | ios::out);
	}

	else if ( toupper(input) == 'C' )
	{
		std::cout << "Enter the name of the file you wish to create.\n";
		std::cin >> filename;

		while (!checkExtension(filename))
		{
			std::cout << "filename must end in extension .txt\n";
			std::cin >> filename;
		}

		file.open(filename, ios::in | ios::out | ios::trunc);
	}

	return filename;
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


