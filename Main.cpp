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

	cmd.setCurrentIndex(0);

	fileVector = storeFile(file);
	cmd.setList(fileVector);


	string mycmd = "sub 100";
	string userInput, userWord;
	int userInt;

	getCmd(mycmd, userInput,userWord, userInt);

	std::cout << userInput << endl << userInt << endl;

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


// maybe rename function? allow to get two words for fucntion man ex: man sub
void getCmd(string line, string& userCmd, string& userWord  , int& userInt)
{
	/* Splits string into a word and number or word and word  */

	// maybe limit user to a max number of lines?

	const int lineSize = line.length();
	int space = 0;
	
	string tempStr;
	int tempInt;

	char *lineArray = new char[lineSize];

	for (int i = 0; i < lineSize; i++)
	{
		*(lineArray + i) = line[i];
		
		// get first word
		if (isalpha(*(lineArray + i)) && space != 1)
		{
			userCmd += *(lineArray + i);
		}
		// get number of lines
		else if (isdigit(*(lineArray + i)) && space != 2)
		{

			tempStr += *( lineArray + i ) ;
		}

		// get second word if number not entered
		else if (isalpha(*(lineArray + i)) && space == 1 && space != 2)
		{
			userWord += *(lineArray + i);
		}
		
		// count spaces in string
		else if ( isspace(*(lineArray + i)) )
			space++;
	}

	

	tempInt = atoi(tempStr.c_str());
	userInt = tempInt;
	
	delete lineArray;
	lineArray = nullptr;
}


