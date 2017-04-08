#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>
#include <cstring>

#include "commands.h"

using namespace std;

void Commands::setCurrentIndex(int index)
{
	currentIndex = index;
}

void Commands::setList( vector<string> vec)
{
	list = vec;
}


void Commands::findStr( string word)
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

	int linesToPrint = listSize - lines;

	for (; linesToPrint < listSize; linesToPrint++)
	{
		std::cout << list[linesToPrint] << endl;
	}
}

void Commands::insert(int lines)
{
	/* Inset X lines to file vector with the current line being the last
	Inserted line */


	string currentLine = list.back();

	int newSize = listSize + lines;

	for (; listSize < newSize; listSize++) {

		if (listSize == newSize - 1) {
			list.push_back(currentLine);
		}
		else
			list.push_back("");

	}
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


void Commands::replace(int lines)
{
	/* Replaces the next X lines including current line
	with empty lines. */

	int newIndex = currentIndex + lines;

	if (newIndex < 0 || newIndex > listSize)
	{
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
		std::cout << newIndex << currentIndex << lines << endl << listSize;
	}

	else
	{
		for (int index = 0; index < lines; index++)
		{
			list[currentIndex + index] = " ";
		}

	}
}

void Commands::del(int lines)
{
	/* Deletes X lines including the current line. */

	if (currentIndex < 0 || currentIndex > listSize)
	{
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
	}
	else
	{
		for (int index = 0; index < lines; index++)
		{
			list.erase(list.begin() + currentIndex);
		}

	}
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
			// !!! NEED TO WORK ON THIS 
			//string temp = list[currentIndex + i];
			//tempList[i].push_back(temp);
		}
	}
}


void Commands::paste()
{

}