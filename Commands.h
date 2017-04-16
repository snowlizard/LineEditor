#ifndef COMMANDS_H
#define COMMANDS_H


#include <vector>
#include <string>

using namespace std;


class Commands {

	

	private:
		static int currentIndex;
		static int listSize;

		int tempSize = tempList.size();

		static vector<string> list;
		vector<string> tempList;
	
	public:
		
		Commands::Commands( vector<string>, int );
	
		vector<string> getList();

		void type( int );
		void findStr( string );
		void insert( int );

		void move( int );
		void moveto( int );
		void replace( int );
		void del( int );

		void copy( int );
		void paste();

		void savefile( fstream& );
		void quit();
		
		void displayFile(); // make into command?

		void parseCmd( string, string&, string&, int& );
		void runCmd( string&, string&, int&) ;


};

#endif // !COMMANDS_H