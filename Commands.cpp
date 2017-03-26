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
		void type(vector<string>, int);
		void findStr(vector<string>, string);
};







void Commands::findStr(vector<string> list, string word)
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

	std::cout << wordCount << word << endl;
}

void Commands::type(vector<string> list, int lines)
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