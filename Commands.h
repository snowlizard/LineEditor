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
		void type(vector<string>&, int);
		void findStr(vector<string>&, string);
		void insert(vector<string>&, int);

};

void Commands::findStr(vector<string>& list, string word)
{
	// counts number of times word is used can be used to replace word as well
	// as locating a word 
	
	int VectorSize = list.size();
	int wordCount = 0;

	for (int index = 0; index < VectorSize; index++)
	{
		string tempStr = list[index].c_str();
		int strSize	   = tempStr.length();

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

}

void Commands::type(vector<string>& list, int lines)
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

void Commands::insert(vector<string>& list, int lines)
{
	/* Inset X lines to file vector with the current line being the last
		Inserted line  
		NOTE: newSize integer is size of list w/ addition of lines minus 1 
		to equal number of lines being added. */
	

	string currentLine = list.back();

	int listSize = list.size();
	int newSize = listSize + lines;

	for (; listSize < newSize; listSize++) {

		if ( listSize == newSize - 1 ) {
			list.push_back(currentLine);
		}
		else
			list.push_back("");

	}
}