#ifndef COMMANDS_H
#define COMMANDS_H


#include <vector>
#include <string>

using namespace std;


class Commands {

	

	private:
		int currentIndex;
		int listSize;

		int tempSize = tempList.size();

		vector<string> list;
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
};

#endif // !COMMANDS_H