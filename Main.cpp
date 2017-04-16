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

void getCmd(string, string&, string&, int&);
void runCmd(string&, string&, int&);


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

	fileVector = storeFile(file);
	
	Commands cmd(fileVector, 0);
	
	string mycmd;
	string userInput, userWord;
	int userInt;

	bool running = true;

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


void getFile(fstream& file)
{
	/* gets file name from user and opens or creates file */

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
