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

	getFile(file);


	Commands cmd;

	cmd.currentIndex = 0;

	fileVector = storeFile(file);
	cmd.list = fileVector;

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
	string filename;

	std::cout << "Enter the name of the file you want to open.\n";
	std::cout << "if the file does not exist it will be created.\n";

	std::cin >> filename;

	while (!checkExtension(filename))
	{
		std::cout << "filename must end in file extension .txt\n";
		std::cin >> filename;
	}

	file.open(filename, ios::in | ios::out);
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



