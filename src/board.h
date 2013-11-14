#ifndef BOARD
#define BOARD

#include <list>
#include <vector>

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

	int charMap (char item){
		if ((item > 64)&&(item < 91)){
			return item-65;
		}
		else if ((item > 96)&&(item < 123)){
			return item-97;
		}
		//temp solution, always affect the 0th row
		return 0;
	};

	void placeTile(char x, int y, T item){
		d_board[charMap(x)][y] = item;
	};

	T getTileAt(char x, int y){
		return d_board[charMap(x)][y];
	};

	// up to 4 in the list, clockwise with no wrap.
	vector<T> getAdjacent(char x, int y){
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
		if( (charMap(x) < d_cols) && adjCheck(getTileAt((x+1), y)) ) {
			adjacent.push_back(getTileAt((x+1), y));
		}
		
		//down
		if ( (y+1 < d_rows)  && adjCheck(getTileAt(x, (y+1))) )  {
			adjacent.push_back(getTileAt(x, (y+1)));
		}
		
		//left 
		if( (charMap(x) > 0) && adjCheck(getTileAt((x-1), y)) ) {
			adjacent.push_back(getTileAt((x-1), y));
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
		return item != 0;
	};

};

#endif
