#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>
#include <cstring>

#include "commands.h"

using namespace std;

int Commands::currentIndex = 0;
int Commands::listSize;
std::vector<string> Commands::list;

vector<string> Commands::tempList;
int Commands::tempSize = tempList.size();

Commands::Commands(vector<string> vec, int index, string filename)
{
	currentIndex = index;
	list = vec;
	listSize = vec.size();

	cFile.open(filename, ios::in | ios::out);
}


vector<string> Commands::getList()
{
	return list;
}


void Commands::findStr( string word )
{
	// counts number of times word is used can be used to replace word as well
	// as locating a word 

	int wordCount = 0;

	for (int index = 0; index < listSize ; index++)
	{
		string tempStr = list[index].c_str();
		int strSize = tempStr.length();

		int pos = 0;

		pos = tempStr.find(word);

		for (int key = 0; key < strSize; key++)
		{
			if (pos != std::string::npos) {
				wordCount += 1;
				pos = tempStr.find(word, pos + 1);
			}

		}
	}

	std::cout << wordCount << word << endl;
}

void Commands::type(int lines)
{
	/** prints X lines before current line and prints
	the current line last.	**/

	if (lines < 0 || lines > listSize)
	{
		std::cout << "ERROR! Out of Bounds.\n";
	}
	else
	{
		for (int i = 0; i < lines; i++)
		{
			std::cout << currentIndex + i << ". " << list[currentIndex + i] << endl;
		}
	}
}

void Commands::insert(int lines)
{
	/* Inset X lines to file vector with the current line being the last
	Inserted line */

	string currentLine = list[currentIndex];


	for ( int i = 0; i < lines; i++ ) {

		if ( i == lines - 1) {
			list.insert(list.begin() + currentIndex + i, currentLine);
		}
		else
			list.insert( list.begin() + currentIndex + i, "" );

	}

	// update listSize
	listSize = list.size();

}

void Commands::move(int numLines)
{
	/* Moves the Current line X lines and prints X lines */

	int newIndex = currentIndex + numLines;

	if (newIndex < 0 || newIndex > listSize)
	{
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
	}

	else
	{
		for (int index = 0; index < numLines; index++)
		{
			std::cout << currentIndex + index << ". " << list[currentIndex + index] << endl;
		}

		currentIndex = newIndex;
	}

}

void Commands::moveto( int num )
{
	if (num < 0 || num > listSize)
	{
		std::cout << "Cannot Move there! Out of bounds.\n";
	}
	else
	{
		currentIndex = num;
		std::cout << currentIndex << ". " << list[currentIndex] << endl;
	}
	
}

void Commands::replace(int lines)
{
	/* Replaces the next X lines including current line
	with empty lines. */

	string userInput;

	int newIndex = currentIndex + lines;

	if (newIndex < 0 || newIndex > listSize)
	{
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
	}

	else
	{
		std::cout << "Enter text for lines you wish to replace.\n";

		for (int index = 0; index < lines; index++)
		{
			std::cout << currentIndex + index << ". ";
			getline(cin, userInput);

			list[currentIndex + index] = userInput;
		}

	}
}

void Commands::del(int lines)
{
	/* Deletes X lines including the current line. */

	if (currentIndex < 0 || currentIndex > listSize)
	{
		std::cout << currentIndex << endl << listSize << endl;
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
	}
	else
	{
		for (int index = 0; index < lines; index++)
		{
			list.erase(list.begin() + currentIndex);
		}
	}
	// update listSize
	listSize = list.size();
}

void Commands::copy(int lines)
{	
	/* Copy X next lines to temporary list */

	// if tempList is not empty, erase its contents
	if ( !tempList.empty() )
	{
		tempList.clear();
	}

	else
	{
		for (int i = 0; i < lines; i++)
		{
			
			string temp = list[currentIndex + i];
			tempList.push_back(temp);
		}
	}
	// update..
	tempSize = tempList.size();
}


void Commands::paste()
{
	/* Paste tempList to List ... inserts them at current line 
	   sets currentLine to last line pasted */
	
	int i = 0;

	for ( ; i < tempSize; i++ )
	{
		list.insert( list.begin() + currentIndex + i, tempList[i] );
	}

	currentIndex = currentIndex + i;
}

void Commands::savefile()
{
	/* Save changes made to file from list vector */

	// BUG! everytime you save file its adding one empty line to add of file.
	std::cout << "Saving File....\n";
	for (int i = 0; i < listSize; i++)
	{
		cFile << list[i] << endl;
	}
}

void Commands::displayFile()
{
	// displays current contents of file
	for (int counter = 0; counter < listSize; counter++)
	{
		std::cout << counter << ". " << list[counter] << endl;
	}
}

void Commands::quit()
{	
	char input;

	std::cout << "Save Progress before exit? [ Y \\ N ]\n";
	std::cin.get(input);
	std::cin.ignore();

	while (toupper(input) != 'Y' && toupper(input) != 'N')
	{
		std::cout << "save file? [ Y \\ N ] \n";
		std::cin.get(input);
		std::cin.ignore();
	}

	if (toupper(input) == 'Y')
	{
		savefile();
		std::cout << "Exiting Program...\n";
		exit(0);
	}
	
	else
	{
		std::cout << "Exiting Program...\n";
		exit(0);
	}
}

void Commands::parseCmd(string line, string& userCmd, string& userWord, int& userInt)
{
	/* Splits string into a word and number or word and word  */

	// reset variables
	userCmd = "";
	userWord = "";
	userInt = 0;


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

			tempStr += *(lineArray + i);
		}

		// get second word if number not entered
		else if (isalpha(*(lineArray + i)) && space == 1 && space != 2)
		{
			userWord += *(lineArray + i);
		}

		// count spaces in string
		else if (isspace(*(lineArray + i)))
			space++;
	}



	tempInt = atoi(tempStr.c_str());
	userInt = tempInt;

	delete lineArray;
	lineArray = nullptr;


}

void Commands::runCmd(string& userInput, string& userWord, int& userInt)
{
	// runs command functions if functions exist/match existing functions

	if (userInput == "type")
	{
		type(userInt);
	}

	else if (userInput == "insert")
	{
		insert(userInt);
	}
	else if (userInput == "move")
	{
		move(userInt);
	}

	else if (userInput == "moveto")
	{
		moveto(userInt);
	}

	else if (userInput == "replace")
	{
		replace(userInt);
	}
	else if (userInput == "del")
	{
		del(userInt);
	}

	else if (userInput == "copy")
	{
		copy(userInt);
	}

	else if (userInput == "paste")
	{
		paste();
	}

	else if (userInput == "save")
	{
		savefile();
	}

	else if (userInput == "cat")
	{
		displayFile();
	}

	else if (userInput == "exit")
	{
		quit();
	}

}