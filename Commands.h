#ifndef COMMANDS_H
#define COMMANDS_H


#include <vector>
#include <string>
using namespace std;


class Commands {
	private:
		int currentIndex;
		vector<string> list;

	public:
		/* CLASS VARIABLES */

		void setCurrentIndex( int );
		void setList( vector<string> ); 

		/* CLASS FUNCTIONS */
	
		void type( int );
		void findStr( string );
		void insert( int );

		void move( int );
		void replace( int );
		void del( int );

		void copy( int );

};

#endif // !COMMANDS_H