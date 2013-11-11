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
	Board(int rows=26, int cols=26) : d_rows(rows), d_cols(cols) {
		for (int i=0; i<rows; i++){
			d_board.push_back(vector<T>(cols));
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
		vector<vector<T> >::iterator itX; //iterator to a vector of T
		vector<T>::iterator itY; //iterator to a vector of T

		int i = 0; // x counter.
		int j = 0; // y counter 
		d_board[charMap(x)][y] = item;
		cout << "Set item: " << d_board[charMap(x)][y] << endl;
	};

	T getTileAt(char x, int y){
		cout << "item: " << d_board[charMap(x)][y] << endl;
		return d_board[charMap(x)][y];
	};

	vector<T> getAdjacent(char x, int y){
		// * * * * *
		// * * u * *
		// * l x r *
		// * * d * *
		// * * * * *

		vector<T> adjacent; 
		//up
		if(charMap(y) > 0){
			adjacent.push_back(getTileAt(x, (y-1)));
		} 
		//down
		if(charMap(y) < 26) {
			adjacent.push_back(getTileAt(x, (y+1)));
		}
		//left 
		if(charMap(x) > 0) {
			adjacent.push_back(getTileAt((x-1), y));
		}
		//right
		if(charMap(x) < 26) {
			adjacent.push_back(getTileAt((x+1), y));
		}

		return adjacent;
	}; // up to 4 in the list

	void print() {

	};
};

#endif
