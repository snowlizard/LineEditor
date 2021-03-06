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

	Commands::filename = filename;
	
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
	int ed;


	int index = currentIndex;

	for (; index < listSize ; index++)
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
				if (wordCount == 1)
					ed = index;
				
			}

		}
	
	}
	if (wordCount == 0)
	{
		std::cout << word << "could not be found.\n";
	}
	else
	{
		std::cout << word << " found in  line " << ed << endl;
		currentIndex = ed;
	}
}

void Commands::sub( string oldStr, string newStr)
{
	string currentLine = list[currentIndex];

	int lineSize = currentLine.length();
	int pos = 0;
	int oldLen = oldStr.length();

	int foundWord = 0;

	for (int counter = 0; counter < lineSize; counter++)
	{
		pos = currentLine.find(oldStr);

		if (pos != std::string::npos)
		{
			currentLine.replace(pos, oldLen, newStr);
			pos = currentLine.find(oldStr, pos + 1);
			foundWord += 1;		
		}
	}


	if (foundWord >= 1)
	{
		// update with replaced word(s)
		list[currentIndex] = currentLine;
	}
	else
		std::cout << "Match not found.\n";
		

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
			if (i + currentIndex > listSize - 1)
			{
				std::cout << "Out of Bounds.\n";
			}
			else
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
	if (num < 0 || num > listSize -1)
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
			if (index + currentIndex > listSize - 1)
			{
				std::cout << "Out of Bounds.\n";
			}
			else
			{
				std::cout << currentIndex + index << ". ";
				getline(cin, userInput);

				list[currentIndex + index] = userInput;
			}
		}

	}
}

void Commands::del(int lines)
{
	/* Deletes X lines including the current line. */

	if ( lines < 0 || lines + currentIndex > listSize)
	{
		std::cout << "ERROR! Index out of bounds, No changes were made.\n";
	}
	else
	{
		for (int index = 0; index < lines; index++)
		{
			if (lines + currentIndex > listSize - 1)
			{
				std::cout << "Out of Bounds! No changes were made.\n";
			}
			else
			{
				list.erase(list.begin() + currentIndex + 1 );
			}
			
		}
	}
	// update listSize
	listSize = list.size();
}

void Commands::copy(int lines)
{	
	/* Copy X next lines to temporary list */

	// erase its contents
	tempList.clear();

	if (lines < 0 || currentIndex + lines > listSize )
	{
		std::cout << " Index out of Bounds.\n";
	}

	else
	{
		for (int i = 0; i < lines; i++)
		{
			if (currentIndex + i > listSize)
			{
				// ignore
			}
			else
			{
				string temp = list[currentIndex + i];
				tempList.push_back(temp);
			}
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
		if (currentIndex + i > listSize - 1)
		{
			// do nothing
		}
		else
			list.insert(list.begin() + currentIndex + i, tempList[i]);
			//list[currentIndex + i] = tempList[i];
	}
	
	listSize = list.size();
	currentIndex = currentIndex + i;
}

void Commands::savefile()
{
	/* Save changes made to file from list vector */

	cFile.open(filename,  ios::out | ios::trunc);
	
	std::cout << "Saving File....\n";

	for (int i = 0; i < listSize -1; i++)
	{
		cFile << list[i] << endl;
		
	}
	cFile.close();
}

void Commands::displayFile()
{
	// displays current contents of list
	for (int counter = 0; counter < listSize; counter++)
	{
		std::cout << counter << ". " << list[counter] << endl;
	}
}

void Commands::clear()
{
	cout << string(40, '\n');
}

void Commands::quit()
{	
	/* Asks user if he/she wishes to  quit the program */
	
	char input;

	std::cout << "Save Progress before exit? [ Y \\ N ]\n";
	std::cin.get(input);
	std::cin.ignore();

	while (toupper(input) != 'Y' && toupper(input) != 'N')
	{
		std::cout << "save file? [ Y \\ N ] \n";
		std::cin.get(input);
	}

	if (toupper(input) == 'Y')
	{
		savefile();
		std::cout << "Exiting Program...\n";
		cFile.close();
		exit(0);
	}
	
	else
	{
		std::cout << "Exiting Program...\n";
		cFile.close();
		exit(0);
	}

}

void Commands::parseCmd(string line, string& userCmd, string& userWord, string& subWord, int& userInt)
{
	/* Splits string into a word and number or word and word  */

	// reset variables
	userCmd  = "";
	userWord = "";
	subWord  = "";
	userInt  = 0;
	

	const int lineSize = line.length();
	int space = 0;

	string tempStr;
	int tempInt;

	char *lineArray = new char[lineSize];

	for (int i = 0; i < lineSize; i++)
	{
		*(lineArray + i) = line[i];

		// get first word
		if (isalpha(*(lineArray + i)) && space == 0)
		{
			userCmd += *(lineArray + i);
		}
		// get number of lines
		else if (isdigit(*(lineArray + i)) && space == 1)
		{

			tempStr += *(lineArray + i);
		}

		// get second word if number not entered
		else if (isalpha(*(lineArray + i)) && space == 1 && space != 2)
		{
			userWord += *(lineArray + i);
		}

		// get third word for sub() // not working right now trying to fix
		else if (isalpha(*(lineArray + i)) && space == 2 && space != 3  )
		{
			subWord += *(lineArray + i);
		}


		// count spaces in string
		else if (isspace(*(lineArray + i)) )
			space++;
	}


	tempInt = atoi(tempStr.c_str());
	userInt = tempInt;

	delete lineArray;
	lineArray = nullptr;


}

void Commands::runCmd(string& userInput, string& userWord, string& subWord, int& userInt)
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

	else if (userInput == "clear")
	{
		clear();
	}

	else if (userInput == "exit")
	{
		quit();
	}

	else if (userInput == "find")
	{
		findStr(userWord);
	}

	else if (userInput == "sub")
	{
		sub(userWord, subWord);

	}

	/*-------------  MANUAL PAGES ---------------*/
	
	else if (userInput == "man" && userWord == "")
	{
		std::cout << "Line Editor Manual\n";
		std::cout << "use the man command followed by a command to read about it.\n";
		std::cout << "ex: man sub \n";
		std::cout << "===== List of Commands =====\n";
		std::cout << " type\n";
		std::cout << " insert\n";
		std::cout << " copy\n";
		std::cout << " paste\n";
		std::cout << " move\n";
		std::cout << " moveto\n";
		std::cout << " cat\n";
		std::cout << " replace\n";
		std::cout << " save\n";
		std::cout << " exit\n";
		std::cout << " del\n";
		std::cout << " clear\n";
		std::cout << " sub\n";
		std::cout << " find\n";
	}
	
	
	else if (userInput == "man" && userWord == "type")
	{
		std::cout << "type #\n";
		std::cout << "Prints the contents of the # lines, including current line.\n";
		std::cout << "ex: type 5 - prints out 5 lines including current line.\n";
	}

	else if (userInput == "man" && userWord == "insert")
	{
		std::cout << "insert #\n";
		std::cout << "insert # lines into the file following the current line\n";
		std::cout << "ex: insert 10 - inserts 10 lines\n";
	}

	else if (userInput == "man" && userWord == "copy")
	{
		std::cout << "copy #\n";
		std::cout << "copies the next # lines including the current line.\n";
		std::cout << "ex: copy 5 - copies 4 lines plus the current one for 5 total lines.\n";
	}

	else if (userInput == "man" && userWord == "paste")
	{
		std::cout << "paste\n";
		std::cout << "paste the contents of copy between the current line and the following line.\n";
		std::cout << "ex: paste \n";
	}

	else if (userInput == "man" && userWord == "move")
	{
		std::cout << "move #\n";
		std::cout << "move and print # lines down.\n";
		std::cout << "move 5 - moves 5 lines down and prints 5 lines.\n";
	}

	else if (userInput == "man" && userWord == "moveto")
	{
		std::cout << "moveto #\n";
		std::cout << "move to # line and print that line.\n";
		std::cout << "ex: moveto 3 - moves to line 3 in file.\n";
	}

	else if (userInput == "man" && userWord == "cat")
	{
		std::cout << "cat\n";
		std::cout << "displays the contents of the files modified state.\n";
	}

	else if (userInput == "man" && userWord == "replace")
	{
		std::cout << "replace #\n";
		std::cout << "replace the next # lines, including the currentline.\n";
		std::cout << "ex: replace 5 - replaces 5 lines with text ( user input )\n";
	}

	else if (userInput == "man" && userWord == "save")
	{
		std::cout << "save\n";
		std::cout << "saves changes made to file.\n";
	}

	else if (userInput == "man" && userWord == "exit")
	{
		std::cout << "exit\n";
		std::cout << "exits the line editor program.\n";
	}

	else if (userInput == "man" && userWord == "del")
	{
		std::cout << "del #\n";
		std::cout << "deletes the next # lines, including the current line.\n";
		std::cout << "ex: del 10\n";
	}

	else if (userInput == "man" && userWord == "clear")
	{
		std::cout << "clear\n";
		std::cout << "clears the screen.\n";
	}

	else if (userInput == "man" && userWord == "find")
	{
		std::cout << "find string\n";
		std::cout << "finds the next occurence of 'string' and makes the line\n";
		std::cout << "containing it the current line.\n";
		std::cout << "ex: find waldo\n";
	}

	else if (userInput == "man" && userWord == "sub")
	{
		std::cout << "sub oldString newString\n";
		std::cout << "replaces every occurence of oldstring in the currentline with newstring.\n";
		std::cout << "ex: sub cat dog   - replaces cat with dog in the current line.\n";
	}
}
