#ifndef COMMANDS_H
#define COMMANDS_H


#include <vector>
#include <string>
using namespace std;


class Commands {
	private:
		int currentIndex;
		int listSize = list.size();
		int tempSize = tempList.size();

		vector<string> list;
		vector<string> tempList;

	public:

		void setCurrentIndex( int );
		void setList( vector<string> ); 
	
		vector<string> getList();

		void type( int );
		void findStr( string );
		void insert( int );

		void move( int );
		void replace( int );
		void del( int );

		void copy( int );
		void paste();

};

#endif // !COMMANDS_H