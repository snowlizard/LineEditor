#ifndef COMMANDS_H
#define COMMANDS_H


#include <vector>
#include <string>

using namespace std;


class Commands {

	

	private:
		static int currentIndex;
		static int listSize;

		static int tempSize;

		static vector<string> list;
		static vector<string> tempList;

		fstream cFile;
	
	public:
		
		Commands::Commands( vector<string>, int , string filename);
	
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

		void savefile( );
		void quit();
		
		void displayFile(); 

		void parseCmd( string, string&, string&, int& );
		void runCmd( string&, string&, int&) ;


};

#endif // !COMMANDS_H