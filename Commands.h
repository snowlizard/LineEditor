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
		
		Commands::Commands(vector<string>, int);
	
		vector<string> getList();

		void type( int );
		void findStr( string );
		void insert( int );

		void move( int );
		void replace( int );
		void del( int );

		void copy( int );
		void paste();

		void savefile(fstream&);
		
		void displayFile(); // make into command?
};

#endif // !COMMANDS_H