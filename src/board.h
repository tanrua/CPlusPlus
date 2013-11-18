#ifndef BOARD
#define BOARD

#include <list>
#include <vector>
#include "group.h"

using namespace std;

template <class T> class Board {
	int d_rows;
	int d_cols;
	vector<vector<T> > d_board;
public:
	//Default to a square board of 26 characters
	Board(int cols=26, int rows=26) : d_rows(rows), d_cols(cols) {
		for (int i=0; i<cols; i++){
			d_board.push_back(vector<T>(rows));
		}
	};

	int charMap (const char& item){
		if ((item > 64)&&(item < 91)){
			return item-65;
		}
		else if ((item > 96)&&(item < 123)){
			return item-97;
		}
		//temp solution, always affect the 0th row
		return 0;
	};

	void placeTile(const char& x, const int& y, const T& item){
		d_board[charMap(x)][y] = item;
	};

	T getTileAt(const char& x, const int& y){
		return d_board[charMap(x)][y];
	};

	// up to 4 in the list, clockwise with no wrap.
	vector<T> getAdjacent(const char& x, const int& y){
		// * * * * *
		// * * u * *
		// * l x r *
		// * * d * *
		// * * * * *

		vector<T> adjacent; 
		//up
		if( (y > 0) && adjCheck(getTileAt(x, (y-1))) ){
			adjacent.push_back(getTileAt(x, (y-1)));
		} 
		
		//right
		char right = x+1;
		if( (charMap(right) < d_cols) && adjCheck(getTileAt(right, y)) ) {
			adjacent.push_back(getTileAt((right), y));
		}
		
		//down
		if ( (y+1 < d_rows)  && adjCheck(getTileAt(x, (y+1))) )  {
			adjacent.push_back(getTileAt(x, (y+1)));
		}
		
		//left
		char left = x-1;
		if( (charMap(left) > 0) && adjCheck(getTileAt((left), y)) ) {
			adjacent.push_back(getTileAt((left), y));
		}

		return adjacent;
	}; 

	void print() {
		for(int j=0; j<d_rows; j++){
			for(int i=0; i<d_cols; i++){
				cout << d_board[i][j] << " ";
			}
			cout << endl;
		}
	};

	bool adjCheck(T item){
		// will turn to != T Group::getDummy();
		return item != 0;
	};

};

#endif
