#pragma once

//#define "commands.h";

// LineEditorTesting.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>

using namespace std;

class Commands {

public:
	int currentIndex; // <-- set current index main function of program

	vector<string> list;
	
	void type( int );
	void findStr( string );
	void insert( int );

	void move( int );
	void replace( int );
	void del( int );


	

};


void Commands::findStr( string word )
{
	// counts number of times word is used can be used to replace word as well
	// as locating a word 

	int VectorSize = list.size();
	int wordCount = 0;

	for (int index = 0; index < VectorSize; index++)
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

void Commands::type( int lines )
{
	/** prints X lines before current line and prints
	the current line last.
	**/
	int listSize = list.size();

	int linesToPrint = listSize - lines;

	for (; linesToPrint < listSize; linesToPrint++)
	{
		std::cout << list[linesToPrint] << endl;
	}
}

void Commands::insert( int lines )
{
	/* Inset X lines to file vector with the current line being the last
	Inserted line
	NOTE: newSize integer is size of list w/ addition of lines minus 1
	to equal number of lines being added. */


	string currentLine = list.back();

	int listSize = list.size();
	int newSize = listSize + lines;

	for (; listSize < newSize; listSize++) {

		if (listSize == newSize - 1) {
			list.push_back(currentLine);
		}
		else
			list.push_back("");

	}
}

void Commands::move( int numLines )
{
	/* Moves the Current line X lines and prints X lines */
	
	int newIndex = currentIndex + numLines;

	if (newIndex < 0 || newIndex > list.size())
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


void Commands::replace( int lines )
{
	/* Replaces the next X lines including current line 
		with empty lines. */

	int listSize = list.size();
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

void Commands::del( int lines )
{
	/* Deletes X lines including the current line. */
	
	int totalDeleted = currentIndex + lines;

	if (currentIndex < 0 || currentIndex > list.size())
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